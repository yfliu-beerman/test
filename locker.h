#ifndef LOCKER_H

#define LOCKER_H

/*
//异常没看
//命名空间是什么
//声明一个有参的构造函数怎么写它的默认参数？
//信号量和互斥量区别 shared？
*/

//#include<exception>
#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

using namespace std;

class sem{
    public:
        sem(int shared = 0,int value = 0);
        ~sem();
        bool post();
        bool wait();
    private:
        sem_t sm;
};

class locker{
    public:
        locker(const pthread_mutexattr_t * attr = NULL);
        ~locker();
        bool lock();
        bool unlock();
        pthread_mutex_t* get_mutex(){
            return &mx;
        }
    private:
        pthread_mutex_t mx;
};

class cond{
    public:
        cond(pthread_mutexattr_t * attr = NULL,pthread_condattr_t *condattr = NULL);
        ~cond();
        bool wait();
        bool signal();
    private:
        locker mx;//它的初始化时机？
        pthread_cond_t cd;
};

#endif