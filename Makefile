LD=g++ -lpthread -Wall
CC=g++ -Wall
try : try.o Thread.o Attr.o Mutex.o MutexAttr.o Event.o Cond.o ThreadLimit.o
	$(LD) -o try try.o Thread.o Attr.o Mutex.o MutexAttr.o Event.o Cond.o ThreadLimit.o
helgrind-fast : try
	valgrind --tool=helgrind ./try
helgrind : try
	valgrind --tool=helgrind --read-var-info=yes ./try
drd : try
	valgrind --tool=drd ./try
memcheck-fast : try
	valgrind --tool=memcheck --track-origins=yes ./try
memcheck : try
	valgrind --tool=memcheck --track-origins=yes --read-var-info=yes ./try
try.o : try.cpp
	$(CC) -c try.cpp 
Mutex.o : Mutex.cpp Mutex.h
	$(CC) -c Mutex.cpp 
Attr.o : Attr.cpp Attr.h
	$(CC) -c Attr.cpp 
Thread.o : Thread.cpp Thread.h
	$(CC) -c Thread.cpp 
MutexAttr.o : MutexAttr.cpp MutexAttr.h
	$(CC) -c MutexAttr.cpp
Event.o : Event.cpp Event.h
	$(CC) -c Event.cpp
Cond.o : Cond.cpp Cond.h
	$(CC) -c Cond.cpp
ThreadLimit.o : ThreadLimit.cpp ThreadLimit.h
	$(CC) -c ThreadLimit.cpp
clean :
	rm -f try *.o
