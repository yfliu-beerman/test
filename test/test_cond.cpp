#include"threadpool.h"

cond cd;
int i = 10;
void* worker(void *para){
    printf("worker is created\n");
    //sleep(20);
    //while(true){
        printf("worker sleep\n");
        cd.wait();
        printf("worker wake and para is %d\n",*(int*)para);
        sleep(20);
        printf("manual sleep end\n");
    //}
    return nullptr;
}

int main(){//结论是不能，可能得看某些锁的attr?
    pthread_t thread;
    printf("start to create\n");
    pthread_create(&thread,NULL,worker,(void*)&i);
    pthread_detach(thread);
    printf("signal once\n");
    sleep(5);
    cd.signal();
    i = 20;//如果只有一个工作进程，并且signal能够让signal之后的等待线程唤醒，那么此时的i是无用的
    cd.signal();
    i = 30;
    cd.signal();
    printf("sign end\n");
    while(true){
       // cd.signal();
    }
    //sleep(100);
}