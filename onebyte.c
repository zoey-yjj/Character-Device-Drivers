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
static ssize_t onebyte_read(struct file *file, char __user *ubuf, size_t size, loff_t *offset)
{
	int bytes_read = 0;

	printk("read: start read function\n");

	if (*offset == 0) {
		if (size < sizeof(char)) {
			return bytes_read;
		}

		if (copy_to_user(ubuf, &devs->data, sizeof(char))) {
			return -EFAULT;
		}
		
		printk("read: data value is %s\n", &devs->data);

		(*offset)++;
		bytes_read++;
	}
	return bytes_read;
}

/* This function is called when someone tries to write into our device file. */
static ssize_t onebyte_write(struct file *file, const char __user *ubuf, size_t size, loff_t *offset)
{
	int bytes_write = 0;

	printk("write: start write function\n");

	if (*offset == 0) {
		if (size < sizeof(char)) {
			return bytes_write;
		}

		if (copy_from_user(&devs->data, ubuf, sizeof(char))) {
			return -EFAULT;
		}

		if (size > sizeof(char)) {
			return -EFBIG;
		}

		printk("write: data value is %s\n", &devs->data);

		(*offset)++;
		bytes_write++;
	}
	return bytes_write;
}

struct file_operations onebyte_fops = { .read = onebyte_read,
					.write = onebyte_write,
					.open = onebyte_open,
					.release = onebyte_close };

/* This function is called when the module is loaded. */
static int onebyte_init(void)
{
	int i, err;

	pr_info("onebyte: init\n");

	/* register the device */
	err = register_chrdev_region(MKDEV(ONEBYTE_MAJOR, 0), ONEBYTE_MINOR_MAX, "onebyte");
	if (err < 0) {
		return err;
	}

	/* initialize devs[i] */
	for (i = 0; i < ONEBYTE_MINOR_MAX; i++) {
		cdev_init(&devs[i].cdev, &onebyte_fops);
		devs[i].cdev.owner = THIS_MODULE;
		devs[i].cdev.ops = &onebyte_fops;
		err = cdev_add(&devs[i].cdev, MKDEV(ONEBYTE_MAJOR, i), 1);
		if (err) {
			pr_err("Error %d adding onebyte%d", err, i);
		}
		// initialize the value to be -1
		devs[i].data = -1;
	}

	return 0;
}

/* This function is called when the module is removed. */
static void onebyte_exit(void)
{
	int i;

	pr_info("onebyte: exit\n");

	/* release devs[i] fields */
	for (i = 0; i < ONEBYTE_MINOR_MAX; i++) {
		cdev_del(&devs[i].cdev);
	}

	/* unregister the device */
	unregister_chrdev_region(MKDEV(ONEBYTE_MAJOR, 0), ONEBYTE_MINOR_MAX);
}

module_init(onebyte_init);
module_exit(onebyte_exit);
