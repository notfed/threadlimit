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

  { Lock<Mutex> guard(console_lock);
    cout << "Thread " << ptr << endl;
  }

  return 0;
}
int main()
{
  ThreadLimit pool(5);
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
  pool.Add(thread_func,(void*)"K");
  pool.Add(thread_func,(void*)"L");
  pool.Add(thread_func,(void*)"M");
  pool.Add(thread_func,(void*)"N");
  pool.Add(thread_func,(void*)"O");
  pool.Add(thread_func,(void*)"P");
  pool.Add(thread_func,(void*)"Q");
  pool.Add(thread_func,(void*)"R");
  pool.Add(thread_func,(void*)"S");
  pool.Add(thread_func,(void*)"T");
  pool.Add(thread_func,(void*)"U");
  pool.Add(thread_func,(void*)"V");
  pool.Add(thread_func,(void*)"W");
  pool.Add(thread_func,(void*)"X");
  pool.Add(thread_func,(void*)"Y");
  pool.Add(thread_func,(void*)"Z");
  pool.Finish();
  return 0;
}
