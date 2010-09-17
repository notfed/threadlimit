#include "Mutex.h"
#include "MutexAttr.h"
#include <stdexcept>
#include <iostream>
#include <pthread.h>
#include <valgrind/helgrind.h>

Mutex::Mutex()
  : m_Owner(pthread_self())
{
  m_Mutex = new pthread_mutex_t();
  MutexAttr mattr(MutexAttr::mutex_errorcheck);
  if(pthread_mutex_init(m_Mutex,mattr)!=0)
    throw std::runtime_error("pthread_mutex_init failed");
  ANNOTATE_HAPPENS_BEFORE(this);
}

Mutex::~Mutex()
{
  ANNOTATE_HAPPENS_AFTER(this);
  if(pthread_equal(m_Owner,pthread_self()))
  {
    if(pthread_mutex_destroy(m_Mutex)!=0)
      std::cerr << "pthread_mutex_destroy failed" << std::endl;
    delete m_Mutex;
  }
}

void Mutex::lock()
{
  ANNOTATE_HAPPENS_AFTER(this);
  if(pthread_mutex_lock(m_Mutex)!=0)
    throw std::runtime_error("pthread_mutex_lock failed");
}

void Mutex::unlock()
{
  ANNOTATE_HAPPENS_AFTER(this);
  if(pthread_mutex_unlock(m_Mutex)!=0)
    throw std::runtime_error("pthread_mutex_unlock failed");
}

Mutex::operator pthread_mutex_t* const()
{
  ANNOTATE_HAPPENS_AFTER(this);
  return m_Mutex;
}
