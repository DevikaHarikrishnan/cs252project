/**
 * timeelapsed.c
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

#define PROC_NAME "seconds" /*define process name*/
#define MODULE_NAME "Procfs Example"/*define module name*/
unsigned long num_interrupts_modload ,num_interrupts_modremove,time_elapsed;

/**
 * This function is called each time the /proc/seconds is read.
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
        int tick_rate = 1000/HZ;/* tick_rate in seconds*/
        num_interrupts_modremove = jiffies;

        if (completed) {/*function is repeatedly called until it returns 0*/
                completed = 0;
                return 0;
        }

        completed = 1;
        time_elapsed = (num_interrupts_modremove - num_interrupts_modload)*tick_rate/1000; /* time elapsed = difference in number of interrupts since module was loaded times frequency of interrupt/1000*/
        rv = sprintf( buffer, "Time elapsed in seconds is = %lu\n", time_elapsed );/* Value of time elapsed in seconds is written to variable buffer which stored on kernel buffer*/
        // copies the contents of kernel memory buffer to variable usr_buf which exists in user space as /proc/seconds can be accessed from user space
        copy_to_user(usr_buf, buffer, rv);
        return rv;
}
static struct proc_ops my_proc_ops = {/* process file operations*/
        
        .proc_read = my_proc_read,
};


/* This function is called when the module is loaded. */
static int proc_init(void)
{

        num_interrupts_modload =jiffies;
        proc_create(PROC_NAME, 0666, NULL, &my_proc_ops);/*create the new /proc/seconds entry using the proc_create function */
        printk(KERN_INFO "/proc/%s created\n", PROC_NAME);
	return 0;
}



/* This function is called when the module is removed. */
static void proc_exit(void) {
        
        // removes the /proc/seconds entry
        remove_proc_entry(PROC_NAME, NULL);
        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}




/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Read Jiffies");
MODULE_AUTHOR("Devika Harikrishnan");