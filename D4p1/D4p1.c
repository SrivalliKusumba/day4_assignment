#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/types.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>



int mychar_open(struct inode *inode, struct file *filp);
int mychar_release(struct inode *inode, struct file *filp);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_release,
};

struct cdev *my_cdev;

static int __init char_init(void)
{
	int r;
	int MAJOR, MINOR;
	dev_t mydev;
	mydev = MKDEV(255,0);
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number = %d\t Minor number = %d\n",MAJOR,MINOR);
	r = register_chrdev_region(mydev, 1, "mychar");
	
	if(r<0)
	{
		printk("\nError");
		return -1;
	}

	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	r = cdev_add(my_cdev, mydev, 1);

	if(r<0)
	{
		printk("Device not created\n");
		return -1;
	}
	return 0;
}

static void __exit char_exit(void)
{
	dev_t mydev;
	int MAJOR, MINOR;
	mydev = MKDEV(255,0);
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t minor number %d\n",MAJOR,MINOR);
	cdev_del(my_cdev);
}

int mychar_open(struct inode *inode,struct file *filp)
{
	printk("Kernel open call\n");
	return 0;
}

int mychar_release(struct inode *inode,struct file *filp)
{
	printk("Kernel release call\n");
	return 0;
}

MODULE_LICENSE("GPL");

module_init(char_init);
module_exit(char_exit);

