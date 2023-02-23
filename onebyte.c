#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

#define ONEBYTE_MAJOR 52
#define ONEBYTE_MINOR_MAX 4

/* This structure holds the device-specific information. */
struct onebyte_data {
	struct cdev cdev;
	char data; // Here stores the one-byte data
} devs[ONEBYTE_MINOR_MAX];

/* This function is called when the device file is opened. */
static int onebyte_open(struct inode *inode, struct file *file)
{
	struct onebyte_data *priv = NULL;
	priv = container_of(inode->i_cdev, struct onebyte_data, cdev);
	file->private_data = priv;
	return 0;
}

/* This function is called when the device file is closed. */
static int onebyte_close(struct inode *inode, struct file *file)
{
	return 0;
}

/* This function is called when someone tries to read from our device file. */
static ssize_t onebyte_read(struct file *file, char __user *ubuf, size_t size, loff_t *offset) {}

/* This function is called when someone tries to write into our device file. */
static ssize_t onebyte_write(struct file *file, const char __user *ubuf, size_t size, loff_t *offset) {}

struct file_operations onebyte_fops = { .read = onebyte_read,
					.write = onebyte_write,
					.open = onebyte_open,
					.release = onebyte_close };

/* This function is called when the module is loaded. */
static int onebyte_init(void) {}

/* This function is called when the module is removed. */
static void onebyte_exit(void) {}

module_init(onebyte_init);
module_exit(onebyte_exit);
