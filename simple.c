/**
 * @file simple.c
 * @author Devika Harikrishnan
 * @brief 
 * coutersy  : Operating System Concepts
 * @version 0.1
 * @date 2021-11-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <linux/init.h> /*header file for all macros*/
#include <linux/module.h>/* Header file needed for all modules*/
#include <linux/kernel.h> /*Header file needed for KERN_ALERT and KERN_INFO*/
#include <linux/hash.h> /*Header file containing hashing functions for use within the kernel*/
#include <linux/gcd.h>/* Header file containing function to find greatest common denominator */
#include <asm/param.h>/* Header file defining tick rate, HZ*/
#include <linux/jiffies.h>/*Header file declaring global variable jiffies, which maintains the number of timer interrupts since system boot*/

/* This function is called when the module is loaded. */
static int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       printk(KERN_INFO "The value of golden ratio prime is %llu\n", GOLDEN_RATIO_PRIME);/*print golden ratio prime defined in hash.h*/
       printk(KERN_INFO "The value of global variable jiffies which maintains the number of timer interrupts since system boot is %lu\n",jiffies);/*print value of jiffies*/
       printk(KERN_INFO "The value of tick rate as defined in asm/param.h is %d\n",HZ);/*Print the rate at which the timer ticks */
       return 0;
}

/* This function is called when the module is removed. */
static void simple_exit(void) {
    /* declaring variables to hold the values of 3300 and 24 */
	unsigned long int first_num = 3300; 
    unsigned int second_num = 24;
    /*print the gcd of 3300 and 24 using gcd function in linux/gcd.h*/
    printk(KERN_INFO "The greatest common denominator of %lu and %u is %lu\n",first_num,second_num,gcd(first_num,second_num));
    printk(KERN_INFO "The value of global variable jiffies which maintains the number of timer interrupts since system boot is %lu\n",jiffies);/*print value of jiffies*/
    /*printk(KERN_INFO "Removing Module\n");*/
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL"); /*Software License details*/
MODULE_DESCRIPTION("Simple Module For Assignment");
MODULE_AUTHOR("Devika Harikrishnan");