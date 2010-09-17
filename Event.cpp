#include "Event.h"
#include "Lock.h"

int Event::Signal()
{
  Lock<Mutex> guard(m_Mutex);
  return m_Cond.Signal();
}

int Event::Broadcast()
{
  Lock<Mutex> guard(m_Mutex);
  return m_Cond.Broadcast();
}

int Event::Wait()
{
  Lock<Mutex> guard(m_Mutex);
  return m_Cond.Wait(m_Mutex);
}
