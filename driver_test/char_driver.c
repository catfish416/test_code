#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <linux/semaphore.h> //信号量有关的函数
#include <linux/wait.h>

MODULE_LICENSE("Dual BSD/GPL");

#define MAJOR_NUM 55 // device num

static ssize_t globalvar_read(struct file *, char *, size_t, loff_t *);
static ssize_t globalvar_write(struct file *, const char *, size_t, loff_t*);
static int globalvar_open(struct inode *inode, struct file *filp);
static int globalvar_release(struct inode *inode, struct file *filp);

//初始化字符设备驱动的file_operations结构体
struct file_operations globalvar_fops =
{
    read:   globalvar_read,
    write:  globalvar_write,
//    open:   globalvar_open,
//    release:globalvar_release,
};

static int global_var = 0;      //"globalvar"设备的全局变量
static int globalvar_count = 0; // globalvar_count记录打开设备的进程数：0,1 
static struct semaphore sem;    //定义信号量
//static DEFINE_SPINLOCK(spin); //Linux内一个套了好几层的宏

static wait_queue_head_t outq; //等待队列头在/include/linux/wait.h中
static int flag = 0;


static int __init globalvar_init(void)
{
    int ret = register_chrdev(MAJOR_NUM, "globalvar", &globalvar_fops); //注册设备驱动
    if (ret) {
        printk("globalvar register failure");
    } else {
        printk("globalvar register success");
        sema_init(&sem, 1);
        init_waitqueue_head(&outq); //初始化等待对列头
    }

    return ret;
}

static void __exit globalvar_exit(void)
{
    unregister_chrdev(MAJOR_NUM, "globalvar");    //注销设备驱动

    printk("globalvar unregister success");
}
/*
static int globalvar_open(struct inode *inode, struct file *filp)
{
    printk("globalvar_open");

    //获得自旋锁 
    spin_lock(&spin);

    //临界资源访问
    if (globalvar_count)
    {
        spin_unlock(&spin);
        return -EBUSY;
    }

    globalvar_count++;

    //释放自旋锁
    spin_unlock(&spin);
    return 0;
}

static int globalvar_release(struct inode *inode, struct file *filp)
{
    printk("globalvar_release");
    globalvar_count--;
    return 0;
}
*/
static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
    printk("globalvar_read");
    /***** case 1 : start *****
    //将global_var从内核空间复制到用户空间
    if (copy_to_user(buf, &global_var, sizeof(int))) {
        return -EFAULT;
    }
    ***** case 1 : end ******/


    /***** case 2 : 信号量 互斥锁 start *****
    //获得信号量 
    if (down_interruptible(&sem)) {
        return -ERESTARTSYS;
    }

    //将global_var从内核空间复制到用户空间
    if (copy_to_user(buf, &global_var, sizeof(int))) {
        up(&sem);
        return -EFAULT;
    }

    //释放信号量 
    up(&sem);
    ***** case 2 : 信号量 互斥锁 end *****/


    //***** case 3 : 等待队列 start *****
    if (wait_event_interruptible(outq, flag != 0)) {
        return -ERESTARTSYS;
    }

    if (down_interruptible(&sem)) {
        return -ERESTARTSYS;
    }

    flag = 0;
    if (copy_to_user(buf, &global_var, sizeof(int))) {
        up(&sem);
        return -EFAULT;
    }
    up(&sem);
    /***** case 3 : 等待队列 end *****/

    return sizeof(int);
}

static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
    printk("globalvar_write");
    /*
    //将用户空间的数据复制到内核空间的global_var
    if (copy_from_user(&global_var, buf, sizeof(int))) {
        return -EFAULT;
    }
    */

    //获得信号量 
    if (down_interruptible(&sem)) {
        return -ERESTARTSYS;
    }

    if (copy_from_user(&global_var, buf, sizeof(int))) {
        up(&sem);
        return -EFAULT;
    }

    //释放信号量 
    up(&sem);

    flag = 1; //flag就是为了判断condition用的
    //通知数据可获得 
    wake_up_interruptible(&outq);

    return sizeof(int);
}

module_init(globalvar_init);
module_exit(globalvar_exit);
