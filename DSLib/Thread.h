#ifndef _DS_THREAD_H_
#define _DS_THREAD_H_  1

#include "Types.h"

#if DS_OS == DS_OSWINDOWS
#   include <windows.h>
#   define DS_THREAD_PROC DWORD WINAPI
#else
#   include <pthread.h>
#   include <unistd.h>
#   define DS_THREAD_PROC void*
#endif

namespace DS
{
   class Thread {
   public:
#if DS_OS == DS_OSWINDOWS
        typedef LPTHREAD_START_ROUTINE ThreadProcPtr;
        typedef HANDLE                 ThreadHandle;
    	typedef DWORD                  ThreadReturn; 
#else
        typedef void* (*ThreadProcPtr)         (void *);
        #define INVALID_HANDLE_VALUE            NULL
        typedef pthread_t*                      ThreadHandle;
        typedef void                            *ThreadReturn; 
#endif

        Thread () {
            _handle = NULL;
        }

        virtual ~Thread () {  
            kill();
        }

        static ThreadHandle detach(ThreadProcPtr threadProc, void *parameter) {
            ThreadHandle handle;
#if DS_OS == DS_OSWINDOWS
            handle = ::CreateThread(NULL, 0, threadProc, parameter, 0, NULL);
            if (handle != INVALID_HANDLE_VALUE) {
                return handle;
            }
            return (ThreadHandle)NULL;
#else
            handle = new pthread_t();
            int err = pthread_create(handle, NULL, threadProc, parameter);
            if (err == 0) {
                return handle;
            } else {
                return (ThreadHandle)NULL;
            }
#endif
        } 

        void start(ThreadProcPtr threadProc, void *parameter = NULL) {
            if (_handle == (ThreadHandle)NULL) {
#if DS_OS == DS_OSWINDOWS
                _handle = ::CreateThread(NULL, 0, threadProc, parameter, 0, NULL);
#else
                _handle = new pthread_t();
                int err = pthread_create(_handle, NULL, threadProc, parameter);
#endif
             }
        } 

        bool    wait(uint32 milliSeconds = 0xFFFFFFFF) {
#if DS_OS == DS_OSWINDOWS
            if (_handle == (ThreadHandle)NULL || _handle == (ThreadHandle)INVALID_HANDLE_VALUE) {
	        return false;
	    }
            
            uint32 res = ::WaitForSingleObject(_handle, milliSeconds);
	    if (res == WAIT_OBJECT_0) {
                return true;
            }
            return false;
#else
            int res = pthread_join(*_handle, NULL);
            if (res == 0)
                return true;
	    return false;
#endif
        } 

        bool kill() {
            if (_handle == (ThreadHandle)NULL || _handle == (ThreadHandle)INVALID_HANDLE_VALUE) {
                return false;
	    }
#if DS_OS == DS_OSWINDOWS
    	    ::TerminateThread(_handle, 0);
#else
    	    pthread_cancel(*_handle);
            delete _handle;
#endif
    	    _handle = (ThreadHandle)NULL;
	        return true;
    	} 

        static void closeUnused(ThreadHandle handle) {
#if DS_OS == DS_OSWINDOWS
            if (handle != NULL && handle != INVALID_HANDLE_VALUE)
                ::CloseHandle(handle);
#endif
        }

        static void sleep (uint32 milliSeconds) {
#if DS_OS == DS_OSWINDOWS
            ::Sleep(milliSeconds);
#else
            usleep(milliSeconds * 1000);
#endif
        } 

protected:

        static const size_t MIN_THREAD_STACK_SIZE = 1024 * 1024;
private:
        Thread (const Thread &);
        Thread &operator= (const Thread &);
        ThreadHandle   _handle;
    };

}

#endif  
