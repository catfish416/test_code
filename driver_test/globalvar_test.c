#include <sys/types.h> //访问_LP64和_ILP32的定义，还包含适当时使用的多个基本派生类型：clock_t,dev_t,off_t,ptrdiff,size_t,ssize_t,time_t 
#include <sys/stat.h> //获得文件的属性，它可以返回一个结构，里面包含文件全部属性 
#include <stdio.h> 
#include <fcntl.h> //设备驱动程序接口是由结构说明，它定义在fcntl.h中 
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define BUILD_TEST_BIN_READ      0
#define BUILD_TEST_BIN_WRITE     0
#define BUILD_TEST_BIN_READ_TIMEOUT     1

int main(void) 
{ 
    int fd, num; //打开"/dev/globalvar"
#if 0
    fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR); //这个函数就是告诉系统，应用程 序要以读写的方式打开/dev/globalvar这个设备, 然后系统再查找相应的驱动程序内的open函数打开设备 
    if (fd != -1 ) {
        //初次读globalvar 
        read(fd, &num, sizeof(int));
        printf("The globalvar is %d\n", num);
        
        //写globalvar 
        printf("Please input the num written to globalvar\n");
        scanf("%d", &num); 
        write(fd, &num, sizeof(int));
        
        //再次读globalvar 
        read(fd, &num, sizeof(int));
        printf("The globalvar is %d\n", num);
        
        //关闭"/dev/globalvar" 
        close(fd); 
    } else {
        printf("Device open failure\n");
    }
#endif
#if BUILD_TEST_BIN_READ
    printf("read test entry:\n");
    fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR); //这个函数就是告诉系统，应用程 序要以读写的方式打开/dev/globalvar这个设备, 然后系统再查找相应的驱动程序内的open函数打开设备 
    if (fd != -1 ) {
        while(1) {
            read(fd, &num, sizeof(int)); //程序将阻塞在此语句，除非有针对globalvar的输入
            printf("The globalvar is %d\n", num);

            //如果输入是0，则退出 
            if (num == 0) {
                close(fd);
                break;
            }
        }
    } else {
        printf("Device open failure\n");
    }
#endif

#if BUILD_TEST_BIN_WRITE
    printf("write test entry:\n");
    fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR); //这个函数就是告诉系统，应用程 序要以读写的方式打开/dev/globalvar这个设备, 然后系统再查找相应的驱动程序内的open函数打开设备 
    if (fd != -1 ) {
        while(1) {
            //写globalvar 
            printf("Please input the num written to globalvar\n");
            scanf("%d", &num); 
            write(fd, &num, sizeof(int));

            //如果输入是0，则退出 
            if (num == 0) {
                close(fd);
                break;
            }
        }
    } else {
        printf("Device open failure\n");
    }
#endif

#if BUILD_TEST_BIN_READ_TIMEOUT

#endif

    return 0;
}