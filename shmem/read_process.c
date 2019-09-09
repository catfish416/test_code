#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define TEXT_SZ 2048
struct shared_use_st
{
    int written_by_you;    //标志用来标明write进程是否写入了数据 written_by_you==1,写入数据，且read进程还没读走
    char some_text[TEXT_SZ];      
};

int main()
{
    key_t key;
    int shmid;
    struct shared_use_st *space;
    int running = 1;
    char buffer[TEXT_SZ];
    //打开共享内存
    key = ftok("./",2);

    shmid = shmget(key,sizeof(struct shared_use_st),IPC_CREAT); 
    if  (-1 == shmid) {
        printf("shmget failed, errno= %d\n", errno);
        return errno;
    }
    //映射共享内存
    space = (struct shared_use_st *)shmat(shmid,NULL,0);     
    if  (NULL == space) {
        printf("shmat failed, errno= %d\n", errno);
        return errno;
    }
    //读取数据
    while(running)
    {
        if(space->written_by_you==1)
        {
            strncpy(buffer,space->some_text,TEXT_SZ);
            space->written_by_you = 0;
            printf("Recieved string :%s",buffer);    
        }    
        if(strncmp(buffer,"end",3)==0)
        {
            running = 0;    
        }
        
    }
    
    //断开映射
    shmdt((const void *)space);
    
    //删除共享内存
    shmctl(shmid,IPC_RMID,0);
    
    return 0;
        
}
