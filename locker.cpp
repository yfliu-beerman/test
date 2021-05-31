#include"locker.h"
//sem
sem::sem(int shared,int value){
    //是否会初始化已初始化的信号量？
    if(sem_init(&sm,shared,value) != 0)
        throw -1;
}

sem::~sem(){
    sem_destroy(&sm);
}

bool sem::post(){
    return sem_post(&sm) == 0;
}

bool sem::wait(){
    return sem_wait(&sm) == 0;
}

//locker
locker::locker(const pthread_mutexattr_t *attr){
    if(pthread_mutex_init(&mx,attr) != 0)
        throw -1;
}

locker::~locker(){
    pthread_mutex_destroy(&mx);
}

bool locker::lock(){
    return pthread_mutex_lock(&mx) == 0;
}

bool locker::unlock(){
    return pthread_mutex_unlock(&mx) == 0;
}

//cond
cond::cond(pthread_mutexattr_t * attr,pthread_condattr_t *condattr):mx(attr){//确实是先执行mx 析构应该是反过来
    if(pthread_cond_init(&cd,condattr) != 0){//!=
        throw -1;//这时是否执行locker的析构函数？都throw了 我寻思也没啥区别
    }        
}

cond::~cond(){
    pthread_cond_destroy(&cd);
}

bool cond::wait(){
    int ret = 0;
    mx.lock();
    ret = pthread_cond_wait(&cd,mx.get_mutex());//只有wait需要互斥锁？
    mx.unlock();
    return ret == 0;
}

bool cond::signal(){
    return pthread_cond_signal(&cd) == 0;
}

