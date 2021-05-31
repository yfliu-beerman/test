#ifndef THREAD_H

#define THREAD_H

#include"locker.h"
#include<list>
#include<vector>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<queue>
#include<assert.h>
using namespace std;
    //线程池退出时与工作线程的同步问题
template<typename T>
class threadpool{//这个东西说是一个池，实际上是工作队列加条件变量做的一个类似生产消费者模型一类的东西 一大堆工作线程sleep，突然有个请求，就赶紧起来一个去工作
    public:
        threadpool(int max_thread = 10,int max_queue = 100);
        void append(T* request);
        ~threadpool();
    private:
        static void* worker(void * arg);//这个arg实际上是this指针
        void run();
    private:
        int max_queue;
        pthread_cond_t cond;//内部的互斥锁用于同步wait sign 额外的互斥锁用于同步请求队列
        //这里的设计使用信号量明显更好，信号量允许线程的v能够接受提前的p，而条件变量似乎不行
        //并非如此，条件变量的写法是如果请求队列不为空则一直运行，而非再次wait，而pv操作可以直接wait
        pthread_mutex_t mtx;
        vector<pthread_t> vec;
        queue<T*> q;
        bool is_stop;//worker是静态，真正的执行函数run非静态，如果工作线程运行到一半，主线程执行析构，是否会导致错误？
        //由于一般不主动执行析构，因此这个想法应该错误，析构时应该主线程退出
};

#endif