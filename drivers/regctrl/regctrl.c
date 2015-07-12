#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/ioctl.h>

#include "regctrl.h"

static ssize_t regctrl_read(struct file * fd, char __user * buf, size_t count, loff_t * offset) {
    return 0;
}
static ssize_t regctrl_write(struct file * fd, const char __user * buf, size_t count, loff_t * offset) {
    return 0;
}
static long regctrl_unlocked_ioctl(struct file * fd, unsigned int cmd, unsigned long arg) {
	if (_IOC_TYPE(cmd) != REGCTRL_MAGIC) {
		return -ENOTTY;
	}
	switch(cmd) {
        case REG_REQ_IOCTL:
        {
            int reg_id;
            reg_id = arg;
            /*
                Set here the params which access the register.
            */
            break;
        }
	}
    return 0;
}

static int regctrl_mmap(struct file * fd, struct vm_area_struct * area) {
    return 0;
}
static int regctrl_open(struct inode * inode, struct file * fd) {
    printk(KERN_INFO "%s\n", __FUNCTION__);
    return 0;
}
static int regctrl_flush(struct file * fd , fl_owner_t id) {
    printk(KERN_INFO "%s\n", __FUNCTION__);
    return 0;
}
static int regctrl_release(struct inode * node, struct file * fd) {
    printk(KERN_INFO "%s\n", __FUNCTION__);
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
	.read = regctrl_read,
	.write = regctrl_write,
	.unlocked_ioctl = regctrl_unlocked_ioctl,
	.mmap = regctrl_mmap,
	.open = regctrl_open,
	.flush = regctrl_flush,
	.release = regctrl_release
};

static int __init regctrl_init(void)
{
    int res;
    printk ("regctrl Init!\n");
    res = register_chrdev(0, DEVICE_NAME, &fops);
    if (res < 0)
	    goto out;
    majorNumber = res;

	regctrl_dev_class = class_create(THIS_MODULE, DEVICE_CLASS);
	if (IS_ERR(regctrl_dev_class)) {
		res = PTR_ERR(regctrl_dev_class);
		goto out_unreg_chrdev;
	}
    return 0;

out_unreg_chrdev:
    unregister_chrdev(majorNumber, DEVICE_NAME);
out:
    printk(KERN_ERR "%s: Driver Initialisation failed\n", __FILE__);
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
