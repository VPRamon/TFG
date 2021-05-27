#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "test_module"

/* Prototypes for device functions */
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);
static int major_num;
static int device_open_count = 0;
int mem[1024];

static struct file_operations file_ops = {
    .read = device_read,
    .write = device_write,
    .open = device_open,
    .release = device_release
};

static ssize_t device_read(struct file *flip, char *buffer, size_t len, loff_t *offset) {
    printk(KERN_ALERT, "reading %d bytes\n", len);
    int pwn[32];
    __memcpy(mem, pwn, len);
    copy_to_user(buffer, mem, len);
    return len;
}

static ssize_t device_write(struct file *flip, const char *buffer, size_t len, loff_t *offset) {
    printk(KERN_ALERT "writing %d bytes.\n", len);
    if ( copy_from_user(mem, buffer, len) )
            return -14LL;
    int pwn[32];
    __memcpy(pwn, mem, len);
    printk(KERN_ALERT "You wrote %s", pwn);
    return len;
}

static int device_open(struct inode *inode, struct file *file) {
    if (device_open_count)
        return -EBUSY;
    device_open_count++;
    try_module_get(THIS_MODULE);
    return 0;
}

static int device_release(struct inode *inode, struct file *file) {
    device_open_count--;
    module_put(THIS_MODULE);
    return 0;
}

static int __init test_module_init(void) {
    major_num = register_chrdev(0, "test_module", &file_ops);
    if (major_num < 0) {
           printk(KERN_ALERT "Could not register device: %d\n", major_num);
           return major_num;
    } else {
            printk(KERN_INFO "Module loaded with device major number %d\n", major_num);
            return 0;
    }
}

static void __exit test_module_exit(void) {
	 unregister_chrdev(major_num, DEVICE_NAME);
	 printk(KERN_INFO "Goodbye, World!\n");
}

module_init(test_module_init);
module_exit(test_module_exit);
