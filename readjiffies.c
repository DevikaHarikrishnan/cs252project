/**
 * readjiffies.c
 *
 * Kernel module that communicates with /proc file system.
 * Operating System Concepts - 10th Edition
 * Authored by Devika Harikrishnan
 *
 * 
 */

#include <linux/init.h>/*Header file for all macros*/
#include <linux/module.h>/* Header file needed for all modules*/
#include <linux/kernel.h>/*Header file needed for KERN_ALERT and KERN_INFO*/
#include <linux/proc_fs.h>/*Header file needed for using proc file system*/
#include <asm/uaccess.h>/* User space memory access -manipulation of user address space*/
#include <linux/jiffies.h>//*Header file declaring global variable jiffies, which maintains the number of timer interrupts since system boot*/
#include <asm/param.h>/* Header file defining tick rate, HZ*/

#define BUFFER_SIZE 128/*define a buffer of 128 bytes so that OS sets aside 128 bytes to be used by this program*/

#define PROC_NAME "jiffies" /*define process name*/
#define MODULE_NAME "Procfs Example"
static char modname[] = "jiffies";

/**
 * This function is called each time the /proc/jiffies is read.
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
        char buffer[BUFFER_SIZE];/*declare buffer of 128 bytes*/
        static int completed = 0;

        if (completed) {/*function is repeatedly called until it returns 0*/
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf( buffer, "Value of jiffies is = %lu\n", jiffies );/* Value of jiffies is written to variable buffer which is stored on kernel buffer*/


        // copies the contents of kernel memory buffer to variable usr_buf which exists in user space as /proc/jiffies can be accessed from user space
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}
static struct proc_ops my_proc_ops = {/* process file operations*/
        
        .proc_read = my_proc_read,
};


/* This function is called when the module is loaded. */
static int proc_init(void)
{
        /*create the new /proc/jiffies entry using the proc_create function */
        proc_create(PROC_NAME, 0666, NULL, &my_proc_ops);
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
        return 0;
}



/* This function is called when the module is removed. */
static void proc_exit(void) {

        // removes the /proc/jiffies entry
        remove_proc_entry(PROC_NAME, NULL);

        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}




/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Read Jiffies");
MODULE_AUTHOR("Devika Harikrishnan");