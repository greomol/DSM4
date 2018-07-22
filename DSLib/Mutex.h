#ifndef _DSMUTEX_H_
#define _DSMUTEX_H_

#include "Types.h"
#if DS_OS == DS_OSWINDOWS
#   include <windows.h>
#else
#   include <pthread.h>
#   include <time.h>
#endif

namespace DS
{
#if DS_OS == DS_OSWINDOWS
    class Mutex {
    public:
        enum reason {
            TIMEOUT,
            FAILED,
            SUCCESS
        };
        Mutex () {
            _systemMutex = ::CreateMutex(NULL, FALSE, NULL);
            _locker = 0;
        }

        ~Mutex () {
            if (_systemMutex == NULL || _systemMutex == INVALID_HANDLE_VALUE) {
            } else {
                ::CloseHandle(_systemMutex);
            }
        }

        int lock () const {
            DWORD err = ::WaitForSingleObject(_systemMutex, INFINITE);
            _locker = ::GetCurrentThreadId();
            return translateError(err);
        }

        int lock (uint32 msec) const {
            DWORD err = ::WaitForSingleObject(_systemMutex, msec);
            _locker = ::GetCurrentThreadId();
            return translateError(err);
        }

        void unlock () const {
            ::ReleaseMutex(_systemMutex);
            _locker = 0;
        }

    protected:
        HANDLE _systemMutex;
        mutable DWORD  _locker;

    private:
        Mutex (const Mutex &);
        Mutex &operator= (const Mutex &);

        int translateError(int err) const {
            if (err == WAIT_TIMEOUT)
                return TIMEOUT;
            if (err == WAIT_OBJECT_0)
                return SUCCESS;
            return FAILED;
        }
    };

#else
    class Mutex {
    public: 
        enum reason {
            TIMEOUT,
            FAILED,
            SUCCESS
        };
        Mutex () {
            pthread_mutexattr_t attr;
            pthread_mutexattr_init(&attr);
            pthread_mutex_init(&_systemMutex, &attr);
        }

        ~Mutex () {
            pthread_mutex_destroy(&_systemMutex);
        }

        int lock () const {
            int err = pthread_mutex_lock(&_systemMutex);
            return translateError(err);
        }

#if DS_OS == DS_OSLINUX        
        int lock (uint32 msec) const {
            timespec t;
            t.tv_sec = msec / 1000;
            t.tv_nsec = (msec % 1000) * 1000000;
            int err = pthread_mutex_timedlock(&_systemMutex, &t);
            return translateError(err);
        }
#endif
        void unlock () const {
            pthread_mutex_unlock(&_systemMutex);
        }

    protected:
        bool _initialized;
        mutable pthread_mutex_t _systemMutex;

    private:
        Mutex (const Mutex &);
        Mutex &operator= (const Mutex &);

        static int translateError(int err) {
#if DS_OS == DS_OSLINUX            
            if (err == ETIMEDOUT)
                return TIMEOUT;
#endif
            if (err == 0)
                return SUCCESS;
            return FAILED;
        }
    };

#endif

    class AutoReleaser {
    public:
        AutoReleaser (Mutex const &mutex) : _scopeMutex (mutex) { 
            _scopeMutex.lock(); 
        }
	~AutoReleaser () { _scopeMutex.unlock(); }

    protected:
        Mutex const &_scopeMutex;
    private:
        AutoReleaser (const AutoReleaser &);
        AutoReleaser &operator= (const AutoReleaser &);
    };

#if DS_OS == DS_OSWINDOWS
    class Event {
    public:
        enum reason {
            TIMEOUT,
            FAILED,
            SUCCESS
        };
        Event (bool manualReset = TRUE) {
            _systemEvent = ::CreateEventW(NULL, manualReset, FALSE, NULL);
        }

        ~Event () {
            if (_systemEvent == NULL || _systemEvent == INVALID_HANDLE_VALUE) { 
            } else {
                ::CloseHandle(_systemEvent);
            }
        }


        int wait (int msec = INFINITE) const {
            DWORD err = ::WaitForSingleObject(_systemEvent, msec);
            return translateError(err);
        }

        void set () const {
            ::SetEvent(_systemEvent);
        }

        void reset () const {
            ::ResetEvent(_systemEvent);
        }

        bool isSet() const {
            return ::WaitForSingleObject(_systemEvent, 0) == WAIT_OBJECT_0;
        }
    public:
        HANDLE _systemEvent;

    private:
        Event(const Event &);
        Event &operator= (const Event &);

        int translateError(int err) const {
            if (err == WAIT_TIMEOUT)
                return TIMEOUT;
            if (err == WAIT_OBJECT_0)
                return SUCCESS;
            return FAILED;
        }
    };
#else
    class Event {
    public:
        enum reason { FAILED, SUCCESS};
        Event (bool manualEvent = true) {
            pthread_mutex_init(&_mutex, NULL); 
            pthread_cond_init(&_systemEvent, &_attr);
            _manual = manualEvent;
            _signalled = false;
            reset();
        }
        ~Event () {
            pthread_mutex_destroy(&_mutex);
            pthread_cond_destroy(&_systemEvent);
        }
        int wait (int msec = 0xFFFFFFFF) const {
            pthread_mutex_lock(&_mutex);
            while (!_signalled) {
                int err = pthread_cond_wait(&_systemEvent, &_mutex);
                if (err != 0) return translateError(err);
            }
            if (!_manual) {
                _signalled = false;
            }
            pthread_mutex_unlock(&_mutex);
            return SUCCESS;
        }
        void set () const {
            pthread_mutex_lock(&_mutex);
            if (!_signalled) {
                _signalled = true;
                pthread_cond_signal(&_systemEvent);
            }
            pthread_mutex_unlock(&_mutex);
        }
        void reset () const {
            pthread_mutex_lock(&_mutex);
            _signalled = false;
            pthread_mutex_unlock(&_mutex);
        }
        bool isSet() const {
            bool retval = false;
            pthread_mutex_lock(&_mutex);
            retval = _signalled;
            pthread_mutex_unlock(&_mutex);
            return retval;
        }
    private:
        mutable pthread_cond_t _systemEvent;
        mutable pthread_condattr_t _attr;
        mutable pthread_mutex_t _mutex;
        mutable bool _manual;
        mutable volatile bool _signalled;
        Event(const Event &);
        Event &operator= (const Event &);
        int translateError(int err) const {
            return err == 0? SUCCESS : FAILED;
        }
    }; 
#endif
}

#endif

