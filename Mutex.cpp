#include "Mutex.h"
#include "MutexAttr.h"
#include <stdexcept>
#include <iostream>
#include <pthread.h>

Mutex::Mutex()
{
  if(pthread_mutex_init(&m_Mutex,0)!=0)
    throw std::runtime_error("pthread_mutex_init failed");
}

Mutex::~Mutex()
{
    if(pthread_mutex_destroy(&m_Mutex)!=0)
      std::cerr << "pthread_mutex_destroy failed" << std::endl;
}

void Mutex::lock()
{
  if(pthread_mutex_lock(&m_Mutex)!=0)
    throw std::runtime_error("pthread_mutex_lock failed");
}

void Mutex::unlock()
{
  if(pthread_mutex_unlock(&m_Mutex)!=0)
    throw std::runtime_error("pthread_mutex_unlock failed");
}
