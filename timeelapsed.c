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

#define BUFFER_SIZE 128

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
        char buffer[BUFFER_SIZE];
        static int completed = 0;
        int tick_rate = 1000/HZ;/* tick_rate in seconds*/
        num_interrupts_modremove = jiffies;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;
        time_elapsed = (num_interrupts_modremove - num_interrupts_modload)*tick_rate/1000; /* time elapsed = difference in number of interrupts since module was loaded times frequency of interrupt/1000*/

        rv = sprintf( buffer, "Time elapsed in seconds is = %lu\n", time_elapsed );

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}
static struct proc_ops my_proc_ops = {
        
        .proc_read = my_proc_read,
};


/* This function is called when the module is loaded. */
static int proc_init(void)
{

        // creates the /proc/hello entry
        // the following function call is a wrapper for
        // proc_create_data() passing NULL as the last argument
        num_interrupts_modload =jiffies;
        proc_create(PROC_NAME, 0666, NULL, &my_proc_ops);
        /*printk(KERN_INFO "The value of global variable jiffies which maintains the number of timer interrupts since system boot is %lu\n",num_interrupts_modload);/*print value of jiffies*/
       /* printk(KERN_INFO "The value of tick rate(frequency of timer interrupt) as defined in asm/param.h is %d\n",HZ);/*Print the rate at which the timer ticks */

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
MODULE_DESCRIPTION("Read Jiffies");
MODULE_AUTHOR("Devika Harikrishnan");