#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("Parent Process ID: %d\n",  getpid());

    for (int i = 0; i < 3; i++)
    {
        fork();
        printf("Process ID: %d ---\n", getpid());
        printf("Process ID: %d 111\n", getpid());
        printf("Process ID: %d 222\n", getpid());
//        fflush(stdout);
    }

    return 0;
}
