#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>

#include "regctrl.h"

long regctrl_unlocked_ioctl(struct file * fd, unsigned int cmd,
                                unsigned long arg) {
    struct regctrl_command* user_req = (struct regctrl_command *)arg;
    int* virt_addr;
	if (_IOC_TYPE(cmd) != REGCTRL_MAGIC) {
        printk(KERN_ERR "REGCTRL_MAGIC number does not match \n");
		return -ENOTTY;
	}

	switch(cmd) {
        case REG_READ_IOCTL:
        {
            struct regctrl_command req;
            if (copy_from_user(&req,(void *) arg,
                    sizeof(struct regctrl_command)) != 0) {
                printk(KERN_ERR "Failed to copy from user \n");
			    return -EFAULT;
		    }
		    virt_addr = ioremap(req.addr, 4);
            req.value = readl(virt_addr);
            mb();
            put_user(req.value, &user_req->value);
            iounmap(virt_addr);
            break;
        }
        case REG_WRITE_IOCTL:
        {
            struct regctrl_command req;
            if (copy_from_user(&req,(void *) arg,
                    sizeof(struct regctrl_command)) != 0) {
                printk(KERN_ERR "Failed to copy from user \n");
			    return -EFAULT;
		    }
            virt_addr = ioremap(req.addr, 4);
            writel(req.value, virt_addr);
            mb();
            iounmap(virt_addr);
            break;
        }
        default:
        {
            printk(KERN_ERR "default \n");
        }
	}
    return 0;
}

int regctrl_open(struct inode * inode, struct file * fd) {
    printk(KERN_INFO "%s\n", __FUNCTION__);
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
	.unlocked_ioctl = regctrl_unlocked_ioctl,
	.open = regctrl_open,
};

static int __init regctrl_init(void)
{
    dev_t curr_dev;
    int res;
    printk(KERN_INFO "regctrl Init!\n");
    res = register_chrdev(0, DEVICE_NAME, &fops);
    if (res < 0){
        printk (KERN_INFO "register_chrdev!\n");
	    goto out;
	}
    majorNumber = res;
    printk(KERN_INFO "majorNumber: %d\n", majorNumber);


	regctrl_dev_class = class_create(THIS_MODULE, DEVICE_CLASS);
	if (IS_ERR(regctrl_dev_class)) {
		res = PTR_ERR(regctrl_dev_class);
		goto out_unreg_chrdev;
	}

    cdev_init(&regctrl_cdev, &fops);
    curr_dev = MKDEV(majorNumber, 0);
    device_create(regctrl_dev_class, NULL, curr_dev, NULL, "regctrl");
    cdev_add(&regctrl_cdev, curr_dev, 1);

    printk(KERN_INFO "Driver will receive ioctl: REG_READ_IOCTL: 0x%x \n",
                REG_READ_IOCTL);
    printk(KERN_INFO "Driver will receive ioctl: REG_WRITE_IOCTL: 0x%x \n",
                REG_WRITE_IOCTL);
    return 0;

out_unreg_chrdev:
    unregister_chrdev(majorNumber, DEVICE_NAME);
out:
    printk(KERN_INFO "Driver Initialisation failed\n");
    return res;
}

static void __exit regctrl_exit(void)
{
    class_destroy(regctrl_dev_class);
    unregister_chrdev(majorNumber, DEVICE_NAME);
}

module_init(regctrl_init);
module_exit(regctrl_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ohad Moisi");
MODULE_VERSION("0.1");
