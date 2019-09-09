#ifndef __SM_COMMON_H__
#define __SM_COMMON_H__
 
#include <pthread.h>
 
#define SM_BUF_SIZE 1024
#define SM_ID 0x1122
 
struct sm_msg
{
	int flag;
	pthread_mutex_t sm_mutex;
	char buf[SM_BUF_SIZE];
};

#endif
