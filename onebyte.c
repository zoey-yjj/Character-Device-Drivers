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


/* This function is called when the module is loaded. */
static int onebyte_init(void) {}

/* This function is called when the module is removed. */
static void onebyte_exit(void) {}

module_init(onebyte_init);
module_exit(onebyte_exit);
