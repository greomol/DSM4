#include "MetaScheduler.h"
#include "Mutex.h"
#include <sstream>

MetaScheduler::MetaScheduler() : _completedQueueIsNotEmpty(false)
{
    _currentSerial = 1000;
    _thread = new DS::Thread();
    _stop.reset();
    _thread->start(_worker, this);
}

MetaScheduler::~MetaScheduler()
{
    _stop.set();	
    _thread->wait();
    delete _thread;
}

string MetaScheduler::getStatus() const
{
    stringstream out;
    DS::AutoReleaser aur(_mutex);
    out << "scheduler status: pending queue size = " << _pendingQueue.size() << endl;
    for (size_t i = 0; i < _pendingQueue.size(); i++) {
        out << "SN=" << _pendingQueue[i].serial;
        out << endl;
    }
    out << "                  input queue size = " << _inputQueue.size() << endl;
    for (size_t i = 0; i < _inputQueue.size(); i++) {
        out << "SN=" << _inputQueue[i].serial;
        out << endl;
    }

    out << "                  completed queue size = " << _completedQueue.size() << endl;
    for (size_t i = 0; i < _completedQueue.size(); i++)	{
        out << "SN=" << _completedQueue[i].serial;
        out << endl;
    }

    return out.str();
}

DS_THREAD_PROC MetaScheduler::_worker(void *args)
{
    MetaScheduler *gs = (MetaScheduler *)args;
    while (gs->_stop.wait(0) == DS::Mutex::TIMEOUT) {
        DS::Thread::sleep(5000);
        gs->purgeCompletedItems();
    }
    return 0;
}

DS::uint32 MetaScheduler::enqueueToPendingQueue(MetaQueueItem const &item, DS::uint64 &serial )
{
    DS::AutoReleaser aur(_mutex);
    QS q;
    q.item = item;
    q.serial = serial;
    q.stamp = ::time(NULL);
    _pendingQueue.push_back(q);
    _pendingSet.insert(serial);
    return DS::Error::OK;
}

DS::uint32 MetaScheduler::enqueueToInputQueue(MetaQueueItem const &item, DS::uint64 &serial )
{
    DS::AutoReleaser aur(_mutex);
    QS q;
    q.item = item;
    q.serial = ++_currentSerial;
    serial = q.serial;
    _inputQueue.push_back(q);
    _inputSet.insert(serial);
    return DS::Error::OK;
}

DS::uint32 MetaScheduler::transferFromPendingQueueToCompletedQueue(DS::uint64 serial, DS::Deserializer const &des, DS::uint32 err)
{
    DS::AutoReleaser aur(_mutex);
    // find the item
    if (_pendingSet.find(serial) == _pendingSet.end()) {
        return DS::Error::ItemNotFound;
    }
    for (deque<MetaScheduler::QS>::iterator it = _pendingQueue.begin(); it != _pendingQueue.end(); it++) {
        if (it->serial == serial) {
            QS qs = *it;
            _pendingQueue.erase(it);
            _pendingSet.erase(serial);
            qs.err = err;
            qs.item.des = des;
            _completedQueue.push_back(qs);
            _completedQueueIsNotEmpty.set();
            return DS::Error::OK;
        }
    }
    return DS::Error::QueueIsEmpty;
}

DS::uint32 MetaScheduler::transferFromPendingQueueToInputQueue(DS::uint64 serial) // , DS::Deserializer const &des)
{
    DS::AutoReleaser aur(_mutex);
    // find the item
    if (_pendingSet.find(serial) == _pendingSet.end()) {
        return DS::Error::ItemNotFound;
    }
    for (deque<MetaScheduler::QS>::iterator it = _pendingQueue.begin(); it != _pendingQueue.end(); it++) {
        if (it->serial == serial) {
            QS qs = *it;
            _pendingQueue.erase(it);
            _pendingSet.erase(serial);
            qs.err = DS::Error::TimeOut;
            // qs.item.des = des;
            _inputQueue.push_back(qs);
            _inputSet.insert(serial);
            return DS::Error::OK;
        }
    }
    return DS::Error::ItemNotFound;
}


void MetaScheduler::purgeCompletedItems()
{
    DS::AutoReleaser aur(_mutex);
    time_t now = ::time(NULL);
    vector<DS::uint64> timeoutedItems;
    for (size_t i = 0; i < _pendingQueue.size(); i++) {
        if (_pendingQueue[i].stamp + _pendingQueue[i].timeout < now) {
            timeoutedItems.push_back(_pendingQueue[i].serial);
	}
    }
    for (size_t i = 0; i < timeoutedItems.size(); i++) {
        transferFromPendingQueueToInputQueue(timeoutedItems[i]);
    }
}

DS::uint32 MetaScheduler::dequeueFromInputQueue(MetaQueueItem &qi, DS::uint64 &serial )
{
    DS::AutoReleaser aur(_mutex);
    if (_inputQueue.size() > 0) {
        MetaScheduler::QS qs = _inputQueue[0];
        qi = qs.item;
        serial = qs.serial;
        _inputQueue.pop_front();
        _inputSet.erase(serial);
        return DS::Error::OK;
    }
    return DS::Error::QueueIsEmpty;
}

DS::uint32 MetaScheduler::dequeueFromCompletedQueue(MetaQueueItem &item, DS::uint64 &serial )
{
    DS::AutoReleaser aur(_mutex);
    if (_completedQueue.size() == 0) {
        return DS::Error::QueueIsEmpty;
    }
    QS qs = _completedQueue[0];
    item = qs.item;
    serial = qs.serial;
    _completedQueue.pop_front();
    return qs.err; // DS::Error::OK;
}

DS::uint32 MetaScheduler::waitForCompleteQueueIsNotEmpty() const
{
    _completedQueueIsNotEmpty.wait();
    return DS::Error::OK;
}

