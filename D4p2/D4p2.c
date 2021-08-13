#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>


int mychar_open(struct inode *inode,struct file *flip);
int mychar_release(struct inode *inode,struct file *flip);
ssize_t mychar_write(struct file *flip, const char *Ubuff, size_t count, loff_t *offp);
ssize_t mychar_read(struct file *flip, char __user *Ubuff, size_t count, loff_t *offp);

struct file_operations fops = 
{ 

	.owner = THIS_MODULE, 
	.open = mychar_open,
	.read = mychar_read,
	.write = mychar_write,
	.release = mychar_release,
};

struct cdev *my_cdev;

static int __init char_init(void)
{
	int r;
	int MAJOR,MINOR;
	dev_t mydev;
	mydev = MKDEV(255,0);
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number = %d\t Minor number = %d\n",MAJOR,MINOR);
	r = register_chrdev_region(mydev, 1, "mychar");

	if(r<0)
	{
		printk("Error\n");
		return -1;
	}

	my_cdev = cdev_alloc();
	my_cdev->ops = &fops;

	r = cdev_add(my_cdev, mydev, 1);
	if(r<0)
	{
		printk("The character device is not created\n");
		unregister_chrdev_region(mydev, 1);
		return -1;
	}
	return 0;
}

static void __exit char_exit(void)
{
	dev_t mydev;
	int MAJOR,MINOR;
	mydev = MKDEV(255,0);
	MAJOR = MAJOR(mydev);
	MINOR = MINOR(mydev);
	printk("Major number %d\t Minor number %d\n",MAJOR,MINOR);
	unregister_chrdev_region(mydev, 1);
	cdev_del(my_cdev);
	printk("Unregistered\n");
}

int mychar_open(struct inode *inode,struct file *filp)
{
	printk("In open system call\n");
	return 0;
}

int mychar_release(struct inode *inode,struct file *flip)
{
	printk("In release method\n");
	return 0;
}

ssize_t mychar_write(struct file *filp,const char __user *Ubuff,size_t count, loff_t *off)
{
	char kbuff[100];
	int r;
	ssize_t ret;
	
        r = copy_from_user((char *)kbuff, (char *)Ubuff, count);
        if(r == 0)
	{
	printk("User data %s\n",kbuff);
        ret = count;
	return ret;
	}

	else if(r>0)
	{
		printk("\n User data %s\n",kbuff);
		printk("\ndata copied %d\n",count-r);
                ret = count-r;
		return ret;
	}
	else
	{
	printk("Error\n");
	ret = -EFAULT;
	return ret;
	}	
}

ssize_t mychar_read(struct file *flip,char __user *Ubuff, size_t count, loff_t *offp)
{
       char kbuff[] = "Kernel to user\n";
       int r;
       ssize_t ret;

       r = copy_to_user((char *)Ubuff, (const char *)kbuff, sizeof(kbuff));
       if(r == 0)
       {
	      printk("\nRead data succesfully %d\n",sizeof(kbuff));
	      ret = sizeof(kbuff);
	      return ret;
       }

       else if(r >0)
       {
	       printk("\nData available %d\n", count-r);
	       ret = count-r;
	       return ret;
       }

       else
       {
	       printk("Error\n");
	       ret = -EFAULT;
	       return ret;
       }

}      
        	      
module_init(char_init);
module_exit(char_exit);

MODULE_LICENSE("GPL");

