#ifndef _REGCTRL_H
#define _REGCTRL_H

struct class *regctrl_dev_class;
struct cdev regctrl_cdev;
struct device *dev;
int majorNumber;

struct regctrl_command {
	int addr;
	int value;
};

long regctrl_unlocked_ioctl(struct file *, unsigned int, unsigned long);
static int regctrl_open(struct inode *, struct file *);

#define DEVICE_CLASS "regctrl"
#define DEVICE_NAME "regctrl"

#define REGCTRL_MAGIC 0xFB
#define REG_REQ_IOCTL _IOW(REGCTRL_MAGIC,  1, int)
#define REG_READ_IOCTL _IOR(REGCTRL_MAGIC,  2, struct regctrl_command)
#define REG_WRITE_IOCTL _IOW(REGCTRL_MAGIC,  3, struct regctrl_command)

#endif //_REGCTRL_H
