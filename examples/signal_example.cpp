//
// Created by echopairs on 5/4/17.
//

#include <thread>
#include <signal_handle.h>

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
    BaseServiceProcess bp;
    bp.installSignalHandle();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while(true)
    {
        fun1();
        fun2();
        fun2();
        fun3();
        fun3();
        fun3();
        fun3();
        fun3();
        fun3();
    }
}
