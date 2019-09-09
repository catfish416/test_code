#include <stdio.h>
#include <stdlib.h>

#define DATA_TXT_FILE "test.txt"


int main()
{
    char str[20];
    char ch;
    int i = 0;

    FILE* fp = fopen(DATA_TXT_FILE, "rt");
    if(NULL == fp)
    {
        printf("***** open :%s failed *****\n", DATA_TXT_FILE);
        return -1;
    }

    int cnt = 0;
    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\t'  || ch =='\n') 
        {
            if(i > 0)
            {
                cnt++;
                str[i++] = '\0';
                printf("line[%d]: %s\n", cnt, str);
                i = 0;

 //               if (cnt == 10)
//                    break;
            }
        }
        else
        {
            str[i++] = ch;
        }
    }

    if ((ch = fgetc(fp)) == EOF)
        printf("end of while\n");
    printf("cnt: %d\n", cnt);

    return 0;
}
