#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define TEXT_SZ 2048

struct shared_use_st
{
    int written_by_you;
    char some_text[TEXT_SZ];      
};

int main(int argc,char **argv)
{
     
    key_t key;
    int shmid;  
    struct shared_use_st *space;
    int running  = 1;
    char buffer[TEXT_SZ];
    //creat shared memory
    key = ftok("./",2);

    shmid = shmget(key,sizeof(struct shared_use_st),IPC_CREAT);
    if  (-1 == shmid) {
        printf("shmget failed, errno= %d\n", errno);
        return errno;
    }
    //attach share memory to space
    space = (struct shared_use_st *)shmat(shmid,NULL,0);
    if  (NULL == space) {
        printf("shmat failed, errno= %d\n", errno);
        return errno;
    }
    //write datas to space
    while(running)
    {
        while(space->written_by_you==1)
        {
            sleep(1);    
        }
        printf("Input strings:");
        fgets(buffer,TEXT_SZ,stdin);
        strncpy(space->some_text,buffer,TEXT_SZ);
        space->written_by_you = 1;
        if(strncmp(buffer,"end",3)==0)
        {
            running = 0;    
        }
       
    }
    
    
    //dis_attach to space
    shmdt((const void *)space);
    //distroy shared memory
  //  shmctl(shmid,IPC_RMID);

    return 0;
}
