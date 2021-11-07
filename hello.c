/**
 * hello.c
 *
 * Kernel module that communicates with /proc file system.
 * Operating System Concepts - 10th Edition
 * Copyright John Wiley & Sons - 2018
 * Modified by Devika Harikrishnan
 *
 * 
 */

#include <linux/init.h>/*Header file for all macros*/
#include <linux/module.h>/* Header file needed for all modules*/
#include <linux/kernel.h>/*Header file needed for KERN_ALERT and KERN_INFO*/
#include <linux/proc_fs.h>/*Header file needed for using proc file system*/
#include <asm/uaccess.h>/* User space memory access -manipulation of user address space*/
#include <linux/jiffies.h>//*Header file declaring global variable jiffies, which maintains the number of timer interrupts since system boot*/

#define BUFFER_SIZE 128

#define PROC_NAME "hello"
#define MESSAGE "Hello World\n"

/**
 * Function prototypes
 */
/*static ssize_t proc_read(struct file *file, char _user *usr_buf, size_t count, loff_t *pos);*/
/**
 * This function is called each time the /proc/hello is read.
 * 
 * This function is called repeatedly until it returns 0, so
 * there must be logic that ensures it ultimately returns 0
 * once it has collected the data that is to go into the 
 * corresponding /proc file.
 *
 * params:
 *
 * file:
 * buf: buffer in user space
 * count:
 * pos:
 */
static ssize_t my_proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf(buffer, "Hello World\n");

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}
static struct proc_ops my_proc_ops = {
        /*.owner = THIS_MODULE,*/
        .proc_read = my_proc_read,
};


/* This function is called when the module is loaded. */
static int proc_init(void)
{

        // creates the /proc/hello entry
        // the following function call is a wrapper for
        // proc_create_data() passing NULL as the last argument
        proc_create(PROC_NAME, 0666, NULL, &my_proc_ops);

        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

	    return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) {

        // removes the /proc/hello entry
        remove_proc_entry(PROC_NAME, NULL);

        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}




/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_AUTHOR("Devika Harikrishnan");