
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/irq.h>
#include <asm/uaccess.h>
#include <asm/irq.h>
#include <asm/io.h>
//#include <asm/arch/regs-gpio.h>
//#include <asm/hardware.h>
#include <linux/poll.h>
#include <linux/cdev.h>
static int hello_open(struct inode *inode, struct file *filp)
{
printk("hello_open\n");
return 0;
}
//构建file_operations结构体
static struct file_operations hello_fops={
.owner=THIS_MODULE,
.open   =   hello_open,
};
static int major;
static struct cdev hello_cdev;
static struct class* hello_class;
static struct class_device* hello_class_dev[3];
static int hello_init(void)
{
dev_t devid;
if(major==0)
{   
alloc_chrdev_region(&devid,0,2,"hello");//主设备号为major，次设备号为0,1则对应该file_operations
major=MAJOR(devid);
//int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count,const char *name)
}
else
{
devid=MKDEV(major,0);
register_chrdev_region(devid,2,"hello");
//int register_chrdev_region(dev_t from, unsigned count, const char *name)
}
cdev_init(&hello_cdev,&hello_fops);
//注册
cdev_add(&hello_cdev,devid,2);
//创建类
hello_class=class_create(THIS_MODULE,"hello");
int i;
for(i=0;i<3;i++)
{   //自动创建设备
hello_class_dev[i]=device_create(hello_class,NULL,MKDEV(major,i),NULL,"hello%d",i);
//hello_class_dev[i]=class_device_create(hello_class,NULL,MKDEV(major,i),NULL,"hello%d",i);
}
return 0;
}
static void hello_exit(void)
{
cdev_del(&hello_cdev);
unregister_chrdev_region(MKDEV(major,0),2);
int i;
for(i=0;i<3;i++)
{
device_destroy(hello_class, MKDEV(major, i));
}
class_destroy(hello_class);
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
