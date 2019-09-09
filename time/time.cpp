#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main( void )
{
     long      i = 10;
     clock_t start, finish;
     double    duration;
     /* 测量一个事件持续的时间*/
     printf( "Time to do %ld empty loops is ", i );
     start = clock();
     while( i-- )
        sleep(1);
     finish = clock();
     duration = (double)(finish - start) / CLOCKS_PER_SEC;
     printf( "%f seconds\n", duration );
     //system("pause");

     return 0;
 }
