#include <stdio.h>
#include <pthread.h>
#include <sched.h>


void *mythread1(void)
{
    printf("this is the 1st thread\n");
    
    int policy = 0;
    struct sched_param param;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setschedpolicy(&attr, SCHED_RR);
    
    pthread_attr_getschedpolicy(&attr, &policy);
    if(policy == SCHED_FIFO){
        printf("Schedpolicy:SCHED_FIFO\n");
    }
    if(policy == SCHED_RR){
        printf("Schedpolicy:SCHED_RR\n");
    }
    if(policy == SCHED_OTHER){
        printf("Schedpolicy:SCHED_OTHER\n");
    }
}

void *mythread2(void)
{
    printf("this is the 2nd thread\n");
}

int main()
{
    int ret = 0;
    pthread_t id1, id2;

    ret = pthread_create(&id1, NULL, (void*)mythread1, NULL);

    if (ret)
    {
        printf("create thread 1 failed \n");
        return -1;
    }

    ret = pthread_create(&id2, NULL, (void*)mythread2, NULL);
    if (ret)
    {
        printf("create thread 2 failed \n");
        return -2;
    }

    pthread_join(id1, NULL);
    pthread_join(id2, NULL);

    return 0;
}
