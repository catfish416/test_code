#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/module.h>
 
static int function_two(void)
{
        extern int function_one(void);
        function_one();
        printk("EXPORT_SYMBOL In Func: %s...\n",__func__);
        return 0;
                                
}
 
static int __init export_symbol_init(void)
{
        printk("EXPORT_SYMBOL  Module two,Init!\n");
        function_two();
        return 0;
                                
}
 
static void __exit export_symbol_exit(void)
{
        printk("EXPORT_SYMBOL  Module two,Exit!\n");
                
}
 
module_init(export_symbol_init);
module_exit(export_symbol_exit);
