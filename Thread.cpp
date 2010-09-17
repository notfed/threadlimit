#include "Thread.h"
#include "Attr.h"
#include "Lock.h"
#include "Mutex.h"
#include <errno.h>
#include <stdexcept>
#include <signal.h>
#include <iostream>
using namespace std;

Thread::Thread(Start_routine_f start_routine, Start_routine_arg_t arg)
  : m_IsDone(false),
    m_StartRoutine(start_routine),
    m_StartRoutineArg(arg)
{
}
void Thread::Start(int state)
{
  Lock<Mutex> stateLock(m_StateLock);
  Attr at(state);
  if(pthread_create(&m_Thread, at, m_StartRoutine, m_StartRoutineArg)!=0) 
    throw std::runtime_error("pthread_create failed");
}
int Thread::Cancel()
{
  Lock<Mutex> stateLock(m_StateLock);
  if(m_IsDone) { errno=ESRCH; return -1; }
  int rc;
  rc = pthread_cancel(m_Thread);
  if(rc==0) m_IsDone = true;
  return rc;
}
int Thread::Kill(int sig)
{
  return pthread_kill(m_Thread,sig);
}
int Thread::Join()
{
  Lock<Mutex> stateLock(m_StateLock);
  if(m_IsDone) { errno=ESRCH; return -1; }
  int rc;
  rc = pthread_join(m_Thread, 0);
  if(rc==0) m_IsDone = true;
  return rc;
}
int Thread::Join(void** value_ptr)
{
  Lock<Mutex> stateLock(m_StateLock);
  if(m_IsDone) { errno=ESRCH; return -1; }
  int rc;
  rc = pthread_join(m_Thread, value_ptr);
  if(rc==0) m_IsDone = true;
  return rc;
}
