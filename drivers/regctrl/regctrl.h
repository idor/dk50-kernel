#ifndef _REGCTRL_H
#define _REGCTRL_H


int majorNumber;
struct class *regctrl_dev_class;
struct device *dev;

static ssize_t regctrl_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t regctrl_write(struct file *, const char __user *, size_t, loff_t *);
static long regctrl_unlocked_ioctl(struct file *, unsigned int, unsigned long);
static int regctrl_mmap(struct file *, struct vm_area_struct *);
static int regctrl_open(struct inode *, struct file *);
static int regctrl_flush(struct file *, fl_owner_t id);
static int regctrl_release(struct inode *, struct file *);

#define DEVICE_CLASS "regctrl"
#define DEVICE_NAME "regctrl"

#define REGCTRL_MAGIC 0xFB
#define REG_REQ_IOCTL _IOW(REGCTRL_MAGIC,  1, int)

#endif //_REGCTRL_H
