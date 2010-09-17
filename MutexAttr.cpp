#include "MutexAttr.h"
#include <iostream>
#include <stdexcept>
typedef MutexAttr::pshared_t pshared_t;
typedef MutexAttr::mutextype_t mutextype_t;
MutexAttr::MutexAttr()
{
  if(pthread_mutexattr_init(&m_MutexAttr)!=0)
    throw std::runtime_error("pthread_mutexattr_init failed");
}
MutexAttr::MutexAttr(pshared_t ps)
{
  if(pthread_mutexattr_init(&m_MutexAttr)!=0)
    throw std::runtime_error("pthread_mutexattr_init failed");
  SetPShared(ps);
}
MutexAttr::MutexAttr(mutextype_t mt)
{
  if(pthread_mutexattr_init(&m_MutexAttr)!=0)
    throw std::runtime_error("pthread_mutexattr_init failed");
  SetType(mt);
}
MutexAttr::MutexAttr(pshared_t ps, mutextype_t mt)
{
  if(pthread_mutexattr_init(&m_MutexAttr)!=0)
    throw std::runtime_error("pthread_mutexattr_init failed");
  SetPShared(ps);
  SetType(mt);
}
MutexAttr::~MutexAttr()
{
  if(pthread_mutexattr_destroy(&m_MutexAttr)!=0)
    std::cerr << "pthread_mutexattr_destroy failed" << std::endl;
}
MutexAttr::operator const pthread_mutexattr_t*()
{
  return &m_MutexAttr;
}

pshared_t MutexAttr::GetPShared()
{
  int result;
  if(pthread_mutexattr_getpshared(&m_MutexAttr,&result)!=0)
    throw std::runtime_error("pthread_mutexattr_getpshared failed");
  return pshared_t(result);
}
void MutexAttr::SetPShared(pshared_t ps)
{
  if(pthread_mutexattr_setpshared(&m_MutexAttr,ps)!=0)
    throw std::runtime_error("pthread_mutexattr_getpshared failed");
}
mutextype_t MutexAttr::GetType()
{
  int result;
  if(pthread_mutexattr_gettype(&m_MutexAttr,&result)!=0)
    throw std::runtime_error("pthread_mutexattr_gettype failed");
  return mutextype_t(result);
}
void MutexAttr::SetType(mutextype_t mt)
{
  if(pthread_mutexattr_settype(&m_MutexAttr,mt)!=0)
    throw std::runtime_error("pthread_mutexattr_settype failed");
}
