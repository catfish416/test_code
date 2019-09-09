#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/semaphore.h>

MODULE_LICENSE("GPL");

#define MAJOR_NUM 666 //主设备号

static ssize_t globalvar_read(struct file *, char *, size_t, loff_t*);
static ssize_t globalvar_write(struct file *, const char *, size_t, loff_t*);
static int globalvar_open(struct inode *inode, struct file *filp);
static int globalvar_release(struct inode *inode, struct file *filp);

//初始化字符设备驱动的 file_operations 结构体
struct file_operations globalvar_fops =
{
    read    : globalvar_read,
    write   : globalvar_write,
//    open    : globalvar_open,
//    release : globalvar_release,
};

static int global_var = 0; //"globalvar"设备的全局变量
static int globalvar_count = 0; // globalvar_count 记录打开设备的进程数:0,1
static struct semaphore sem;
//static spinlock_t spin = SPIN_LOCK_UNLOCKED;    //Linux 内一个套了好几层的宏
static DEFINE_SPINLOCK(spin);

static int __init globalvar_init(void)
{
    int ret;
    //注册设备驱动
    ret = register_chrdev(MAJOR_NUM, "globalvar", &globalvar_fops);
    if (ret)
    {
        printk("globalvar register failure");
    }
    else
    {
        printk("globalvar register success");
    }
    return ret;
}

static void __exit globalvar_exit(void)
{
    unregister_chrdev(MAJOR_NUM, "globalvar");
#if 0
    int ret;
    //注销设备驱动
    ret = unregister_chrdev(MAJOR_NUM, "globalvar");
    if (ret)
    {
        printk("globalvar unregister failure");
    }
    else
    {
        printk("globalvar unregister success");
    }
#endif
}

static int globalvar_open(struct inode *inode, struct file *filp)
{
    //自旋锁是为了保证只有一个应用程序访问该字符设备
    //获得自旋锁
    spin_lock(&spin);
    //第一次打开设备时,将其锁住,此时 globalvar_count=0;执行globalvar_count++;然后globalvar_count=1;释放自旋锁 第二次打开设备时,将其锁住,此时 globalvar_count=1;执行spin_unlock(&spin); return - EBUSY;返回-1,应用层的 open 运行printf("Device open failure\n");
    //临界资源访问
    if (globalvar_count)
    {
        //globalvar_count=1;      释放自旋锁第二次打开设备时,将其锁住,
        spin_unlock(&spin);
        return - EBUSY;         //此时 globalvar_count=1;执行 spin_unlock(&spin); return - EBUSY; //返回-1,应用层的 open 运行
    }
    globalvar_count++; 
    //printf("Device open failure\n");
    //释放自旋锁
    spin_unlock(&spin);
    return 0;
}

static int globalvar_release(struct inode *inode, struct file *filp)
{
    globalvar_count--;
    return 0;
}

static ssize_t globalvar_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
    //获得信号量
    if (down_interruptible(&sem))
    {
        return - ERESTARTSYS;
    }

    //将 global_var 从内核空间复制到用户空间
    if (copy_to_user(buf, &global_var, sizeof(int)))
    {
        up(&sem);
        return - EFAULT;
    }

    //释放信号量
    up(&sem);

    return sizeof(int);
}

static ssize_t globalvar_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
    //获得信号量
    if (down_interruptible(&sem))
    {
        return - ERESTARTSYS;
    }

    //将用户空间的数据复制到内核空间的 global_var
    if (copy_from_user(&global_var, buf, sizeof(int)))
    {
        up(&sem);
        return - EFAULT;
    }

    up(&sem);
    return sizeof(int);
}

module_init(globalvar_init);
module_exit(globalvar_exit);
