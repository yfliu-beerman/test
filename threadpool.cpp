#include"threadpool.h"
//异常和线程什么关系
template<typename T>
threadpool<T>::threadpool(int max_thread,int max_queue):vec(0,max_thread),is_stop(false),max_queue(max_queue){
    //这里应该有个输入检测的，但是对于这种我更倾向于有个额外的wrapper?
    //列表初始化怎么做输入检测？
    pthread_cond_init(&cond,NULL);
    pthread_mutex_init(&mtx,NULL);
    for(int i = 0;i < max_thread;i++){
        int flag = pthread_create(&vec[i],NULL,worker,(void*)this);//这里违背了muduo的不要在构造函数交出this的原则
        assert(!flag);
        flag = pthread_detach(vec[i]);
        assert(!flag);
    }
}

template<typename T>
threadpool<T>::~threadpool(){
    is_stop = true;
}

template<typename T>
void threadpool<T>::append(T* request){
    pthread_mutex_lock(&mtx);
    if(q.size() >= max_queue){
        throw -1;
    }
    q.push(request);
    pthread_mutex_unlock(&mtx);
    
}

template<typename T>
void* threadpool<T>::worker(void *arg){
    (threadpool*)arg->run();
    return arg;
}
template<typename T>
void threadpool<T>::run(){
    while(!is_stop){
        pthread_mutex_lock(&mtx);
        while(q.size() == 0){//这边允许获得互斥锁+做判断即可允许，书上是起手p操作等资源，然后获得互斥锁开始操作队列。
            pthread_cond_wait(&cond,&mtx);//关键在于wait出来后需要再次检查是否size非0
        }
        T* tt = q.front();
        q.pop();
        pthread_mutex_unlock(&mtx);
        T->process();//这个t就是http_conn 但是这个写法是错误的
    }
}