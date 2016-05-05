/*********************************************************************
  Copyright (C), 1990-2016, HangZhou RED HEAT Tech. Co., Ltd.
  FileName: sig.cc
  Author  : pairs & 736418319@qq.com
  Version : 1.0
  Date    : 2016/05/05
  Description:
        how to deal with signal in Multi-threading and  
        getperformance bottleneck with gperftools
  Function List:
  History:
      <author>    <time>    <version>    <desc>
        pairs     16/05/05      1.0     build this moudle
*********************************************************************/
#include <iostream>
#include <signal.h>
#include <google/heap-checker.h> 
#include <google/heap-profiler.h> // for heap with HeapProfilerStart,HeapProfileStop,HeapProfileDump
#include <google/profiler.h>      // for cpu with ProfileStart,ProfileStop,ProfilerFlush
#include <thread>                 // c11 for multi-thread

using namespace std;
// handle sig function, switch 60 is start produce xxx.profile, 61 is stop
void signalHandle(int sig)
{
    static bool profilerStarted = false;
    if (SIGKILL == sig || SIGINT == sig || SIGTERM == sig)
    {
        if (SIG_ERR == ::signal(sig, NULL));
        {}
    }
    else if (60 == sig)
    {
        if (profilerStarted)
        {
            // flush profile to file
            ProfilerFlush();
        }
        else
        {
            // begin produce profile to /tmp/sig.profile
            cout << "begin start" << endl;
            ProfilerStart("/tmp/sig.profile");
        }
    }
    else if (61 == sig)
    {
        // stop produce profile
        cout << "stop " << endl;
        ProfilerStop();
    }
}


// the thread for deal with sig
void sigThreadFun()
{
    sigset_t waitset;
    siginfo_t info;
    int rc;
    sigemptyset(&waitset);
    sigaddset(&waitset, SIGKILL);
    sigaddset(&waitset, SIGINT);
    sigaddset(&waitset, SIGTERM);
    sigaddset(&waitset, 60);
    sigaddset(&waitset, 61);
    while(1)
    {
        struct timespec tm = {1, 0};
        rc = sigtimedwait(&waitset, &info, &tm);
        if (rc > 0)
        {
            signalHandle(info.si_signo);
        }
        else if (rc == 0)
        {
            cout << "time out" << endl;
        }
    }

}

// install signalHandle to let us deal with signal in special thread
// let means all signals will be handle in this special thread  
std::thread installSignalHandle()
{
    sigset_t bset,oset;
    sigemptyset(&bset);
    sigaddset(&bset, SIGKILL);
    sigaddset(&bset, SIGINT);
    sigaddset(&bset, SIGTERM);
    sigaddset(&bset, 60);
    sigaddset(&bset, 61);

    sigaddset(&bset, 60);
    sigaddset(&bset, 61);
    pthread_sigmask(SIG_BLOCK, &bset, &oset);
  
    // create sig handle thread
    std::thread t(sigThreadFun);
    return t;
}



// for test
void fun1()
{
    char *fun1 = new char(100);
    delete fun1;
    fun1 = NULL;
}

void fun2()
{
    char *fun2 = new char(100);
    delete fun2;
    fun2 = NULL;
}

void fun3()
{
    char *fun3 = new char(100);
    delete fun3;
    fun3 = NULL;
}


// main begin
int main()
{
    std::thread t;
    t = installSignalHandle();
    cout << "hello world" << endl;
    while(1)
    {
        for (int i = 0; i < 10; i++)
        {
            fun1();
        }
        fun2();
        fun2();
        fun3();
        fun3();
        fun3();
        fun3();
        fun3();
                
    }
   t.join(); 
}


/*
g++  sig.cc -std=c++11 -lprofiler -lpthread -ltcmalloc
how to deal with pprof
pprof --dot /home/test/threadSigHandle/a.out sig.profile >>sig.dot
dot -Tpng sig.dot>>sig.png
*/


