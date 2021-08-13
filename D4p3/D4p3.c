#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");

int mychar_open(struct inode *inode,struct file *flip);
int mychar_release(struct inode *inode,struct file *flip);

struct file_operations fops = 
{
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_release,
};

struct cdev *my_cdev;

dev_t mydev;

static int __init char_init(void)
{
	int r;
        int MAJOR,MINOR;	

	r = alloc_chrdev_region(&mydev, 0, 1,"mychar");

	if(r<0)
	{
		printk("Error\n");
		return -1;
	}
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number = %d\t Minor number = %d\n ", MAJOR,MINOR);

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
	unregister_chrdev_region(mydev, 1);
	cdev_del(my_cdev);
	printk("Exit\n");
}

int mychar_open(struct inode *inode, struct file *flip)
{
	printk("File open operation\n");
	return 0;
}

int mychar_release(struct inode *inode, struct file *flip)
{
	printk("File release operation\n");
	return 0;
}

module_init(char_init);
module_exit(char_exit);


