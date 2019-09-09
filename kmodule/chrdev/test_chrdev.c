#include <sys/types.h>    //访问_LP64 和_ILP32 的定义,还包含适当时使用的多个基本派生类型:clock_t,dev_t,off_t,ptrdiff,size_t,ssize_t,time_t
#include <sys/stat.h>    //获得文件的属性,它可以返回一个结构,里面包含文件全部属性
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    int fd, num;
    
    //打开"/dev/globalvar"
    fd = open("/dev/globalvar", O_RDWR, S_IRUSR | S_IWUSR); //这个函数就是告诉系统,应用程序要以读写的方式打开/dev/globalvar 这个设备, 然后系统再查找相应的驱动程序内的 open 函数打开设备
    if (fd != -1)
    {
        //初次读 globalvar
        read(fd, &num, sizeof(int));
        printf("The globalvar is %d\n", num);
        
        //写 globalvar
        printf("Please input the num written to globalvar\n");
        scanf("%d", &num);
        write(fd, &num, sizeof(int));
        
        //再次读 globalvar
        read(fd, &num, sizeof(int));
        printf("The globalvar is %d\n", num);
        
        //关闭"/dev/globalvar"
        close(fd);
    }
    else
    {
        printf("Device open failure\n");
    }

    return 0;
}
