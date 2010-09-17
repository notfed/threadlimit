#include <iostream>
#include "Thread.h"
#include "Lock.h"
#include "Semaphore.h"
#include "ThreadLimit.h"
using namespace std;
Mutex console_lock;
void* thread_func(void* arg)
{
  sleep(1);
  const char *ptr = (const char*)arg;
  {
    Lock<Mutex> guard(console_lock);
    cout << "Thread " << ptr << endl;
  }
  return 0;
}
int main()
{
  ThreadLimit pool(2);
  pool.Add(thread_func,(void*)"A"); 
  pool.Add(thread_func,(void*)"B");
  pool.Add(thread_func,(void*)"C");
  pool.Add(thread_func,(void*)"D");
  pool.Add(thread_func,(void*)"E");
  pool.Add(thread_func,(void*)"F");
  pool.Add(thread_func,(void*)"G");
  pool.Add(thread_func,(void*)"H");
  pool.Add(thread_func,(void*)"I");
  pool.Add(thread_func,(void*)"J");
  cin.get(); 
  return 0;
}
