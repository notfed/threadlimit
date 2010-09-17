#include "Cond.h"
#include "Mutex.h"
#include <stdexcept>
#include <iostream>
#include <pthread.h>

Cond::Cond()
  : m_Owner(pthread_self())
{
  m_Cond = new pthread_cond_t();
  if(pthread_cond_init(m_Cond,0)!=0)
    throw std::runtime_error("pthread_cond_init failed"); 
}
Cond::~Cond()
{
  if(pthread_equal(m_Owner,pthread_self()))
  {
    if(pthread_cond_destroy(m_Cond)!=0)
      std::cerr << "pthread_cond_destroy failed" << std::endl; 
    delete m_Cond;
  }
}
Cond::operator pthread_cond_t* const() 
{ 
  return m_Cond; 
}

int Cond::Wait(Mutex& mutex)
{
  return pthread_cond_wait(m_Cond,mutex);
}

int Cond::Signal()
{
  return pthread_cond_signal(m_Cond);
}
int Cond::Broadcast()
{
  return pthread_cond_broadcast(m_Cond);
}
