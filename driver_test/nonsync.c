#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#define MAX_LEN 100

void input_handler(int num)
{
    char data[MAX_LEN];
    int len; //读取并输出STDIN_FILENO上的输入
    len = read(STDIN_FILENO, &data, MAX_LEN);
    data[len] = 0;
    printf("input available: %s\n", data);
}

int main(void)
{
    int oflags; //启动信号驱动机制
    signal(SIGIO, input_handler);
    fcntl(STDIN_FILENO, F_SETOWN, getpid());
    oflags = fcntl(STDIN_FILENO, F_GETFL);
    fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);
    //最后进入一个死循环，程序什么都不干了，只有信号能激发input_handler的运行
    //如果程序中没有这个死循环，会立即执行完毕
    while (1);

    return 0;
}