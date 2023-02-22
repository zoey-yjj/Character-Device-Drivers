#include <linux/cdev.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

/* This function is called when the module is loaded. */
static int onebyte_init(void) {}

/* This function is called when the module is removed. */
static void onebyte_exit(void) {}

module_init(onebyte_init);
module_exit(onebyte_exit);
