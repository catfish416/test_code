#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
 
static int function_one(void)
{
                printk("EXPORT_SYMBOL  In Func: %s...\n",__func__);
                        return 0;
                        
}
 
EXPORT_SYMBOL(function_one);
 
static int __init export_symbol_init(void)
{
                printk("EXPORT_SYMBOL  Module one,Init!\n");
                        return 0;
                        
}
 
static void __exit export_symbol_exit(void)
{
                printk("EXPORT_SYMBOL  Module one,Exit!\n");
                
}
 
module_init(export_symbol_init);
module_exit(export_symbol_exit);
