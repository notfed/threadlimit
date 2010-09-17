#ifndef MUTEXATTR_H 
#define MUTEXATTR_H 
#include <pthread.h>
class MutexAttr
{
  pthread_mutexattr_t m_MutexAttr;
public:
  enum pshared_t { 
    pshared_private=PTHREAD_PROCESS_PRIVATE, 
    pshared_shared =PTHREAD_PROCESS_SHARED 
  };
  enum mutextype_t { 
    mutex_normal = PTHREAD_MUTEX_NORMAL,
    mutex_errorcheck = PTHREAD_MUTEX_ERRORCHECK,
    mutex_recursive = PTHREAD_MUTEX_RECURSIVE,
    mutex_default = PTHREAD_MUTEX_DEFAULT 
  };
  virtual ~MutexAttr();
  MutexAttr();
  MutexAttr(pshared_t);
  MutexAttr(mutextype_t);
  MutexAttr(pshared_t,mutextype_t);
  operator const pthread_mutexattr_t*();
  

  pshared_t GetPShared();
  void SetPShared(pshared_t);

  mutextype_t GetType();
  void SetType(mutextype_t);
};
#endif
