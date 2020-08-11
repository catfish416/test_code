#include <stdio.h>
#include <stdlib.h>
#include "list.h"
 
#define SZ 32
#define CNT 30
 
struct student {
	char name[SZ];
	int num;
	struct list_head list;
};


void demo_init(struct list_head *list_head)
{
    struct student *std;

    INIT_LIST_HEAD(list_head);
    for (int i = 0; i < CNT; i++) {
        std = (struct student *)malloc(sizeof(struct student));
        if (!std) {
            printf("malloc failed!\n");
            break;
        }
        std->num = 10086 + i;
        snprintf(std->name, SZ, "robot %d", i);
        // add list
        list_add_tail(&std->list, list_head);
    }

    if (list_empty(list_head))
        printf("check list empty! 1\n");
}

void search_list(struct list_head *list_head)
{
    int i = 0;
    struct list_head *list_find;
    struct student *p_find;

    list_for_each(list_find, list_head) {
        p_find = list_entry(list_find, struct student, list);
        printf("point: %p, value %d : name = %s, number = %d\n", 
                        list_find, i++, p_find->name, p_find->num);
    }
    printf("total %d \n", i);

    if (list_empty(list_head))
        printf("check list empty! 2\n");
}

void demo_exit(struct list_head *list_head)
{
    int i = 0;
    struct list_head *list_remove, *list_remove2;
    struct student *p_del;

    list_for_each_safe(list_remove, list_remove2, list_head) {
        list_del(list_remove);
        p_del = list_entry(list_remove, struct student, list);
        free(p_del);
        printf("node %d has been removed from the double list\n", i++);
    }

    if (list_empty(list_head))
        printf("the list is empty 3 !\n");
}

int main()
{
    struct list_head list_head;

    demo_init(&list_head);
    search_list(&list_head);
    demo_exit(&list_head);

    return 0;
}
