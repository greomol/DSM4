#ifndef _META_SCHEDULER_H_
#define _META_SCHEDULER_H_ 1

#include <deque>
#include <string>
using namespace std;
#include "Types.h"
#include "MetaQueueItem.h"
#include "Mutex.h"
#include "Thread.h"
#include <time.h>
#include <set>

class MetaScheduler
{
public:
    MetaScheduler();
    ~MetaScheduler();
    string getStatus() const;
    DS::uint32      enqueueToInputQueue    (MetaQueueItem const &item, DS::uint64 &serial);
    size_t          getInputQueueSize() const { return _inputQueue.size(); }
    size_t          getPendingQueueSize() const { return _pendingQueue.size(); }
    size_t          getCompletedQueueSize() const { return _completedQueue.size(); }

    DS::uint32      dequeueFromCompletedQueue  (MetaQueueItem &item,       DS::uint64 &serial);
    DS::uint32	    dequeueFromInputQueue      (MetaQueueItem &qi,         DS::uint64 &serial );
    DS::uint32      enqueueToPendingQueue      (MetaQueueItem const &item, DS::uint64 &serial);
    DS::uint32	    transferFromPendingQueueToCompletedQueue(DS::uint64 serial, DS::Deserializer const &des, DS::uint32 err);
    DS::uint32	    waitForCompleteQueueIsNotEmpty() const;

private:
    DS::uint32	    getQueueStatus(DS::uint64 serial, int &status, DS::uint32 &err);


    DS::uint32	    transferFromPendingQueueToInputQueue (DS::uint64 serial); 
    DS::uint32      dequeueFromPendingQueue(MetaQueueItem &item, DS::uint64 &serial);
    DS::uint32      enqueueToCompletedQueue(MetaQueueItem const &item, DS::uint64 &serial);
    void            purgeCompletedItems();
    struct QS {
        MetaQueueItem   item;
        DS::uint64      serial;
        DS::uint32      err;
        time_t          stamp;
        int             timeout;
        QS() {
            serial = 0;
            err = DS::Error::OK;
            stamp = 0;
            timeout = 60;
	}
    };

    deque<QS>       _inputQueue;
    set<DS::uint64> _inputSet;
    DS::Event       _inputQueueIsEmptyEvent;

    deque<QS>       _pendingQueue;
    set<DS::uint64> _pendingSet;

    deque<QS>       _completedQueue;
    DS::Event       _completedQueueIsNotEmpty;

    DS::Thread *_thread;
    DS::Event   _stop;
    DS::Mutex	_mutex;
    static DS_THREAD_PROC _worker(void *);
    DS::uint64 _currentSerial;
};
#endif

