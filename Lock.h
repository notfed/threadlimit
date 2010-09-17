#ifndef LOCK_H
#define LOCK_H
#include "Semaphore.h"
template <class T>
class Lock
{
  T& m_Sem;
public:  
  Lock(T&);
  virtual ~Lock();
};

template <class T>
Lock<T>::Lock(T& newSem) 
  : m_Sem(newSem)
{ 
  m_Sem.lock();
}

template <class T>
Lock<T>::~Lock()
{
  m_Sem.unlock();
}

#endif
