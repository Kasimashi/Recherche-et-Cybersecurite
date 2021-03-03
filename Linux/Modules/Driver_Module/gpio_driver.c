///////////////////////////////////////////////////////////////////////////////
// Includes
///////////////////////////////////////////////////////////////////////////////
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/gpio.h>
#include <linux/kthread.h>
#include <linux/delay.h>

///////////////////////////////////////////////////////////////////////////////
// Defines
///////////////////////////////////////////////////////////////////////////////
#define BUFF_SIZE 256 
#define GPIO_CTRL_OUT 4

MODULE_LICENSE("GPL");        
MODULE_AUTHOR("Pierrick Curt");       
MODULE_DESCRIPTION("My first char driver"); 
MODULE_VERSION("1.0");

///////////////////////////////////////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////////////////////////////////////
static int blink_period_ms = 100;
static struct task_struct *task;            ///< The pointer to the thread task
static char kernel_buf[BUFF_SIZE] = {"Hello\n"};

// Parameters for the module
module_param(blink_period_ms, int, S_IWUSR|S_IRUGO|S_IWGRP);
MODULE_PARM_DESC(blink_period_ms, "Blink period in ms");


///////////////////////////////////////////////////////////////////////////////
// Private functions
///////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
// Handler task function
///////////////////////////////////////////////////////////////////////////////
static int flash(void *arg){
    while(!kthread_should_stop()){ 
        set_current_state(TASK_RUNNING);
        msleep(blink_period_ms/2);
        gpio_set_value(GPIO_CTRL_OUT, !gpio_get_value(GPIO_CTRL_OUT));        
    }

    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function called when an open is done (before a read or a write)
///////////////////////////////////////////////////////////////////////////////
static int my_open(struct inode *inode, struct file *file)
{
    pr_info("GPIO Control: Open\n");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function called when an close is done (after a read or a write)
///////////////////////////////////////////////////////////////////////////////
static int my_close(struct inode *inodep, struct file *filp)
{
    pr_info("GPIO Control: Close\n");
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function called when a write is done 
///////////////////////////////////////////////////////////////////////////////
static ssize_t my_write(struct file *file, const char __user *buf,
		       size_t len, loff_t *ppos)
{
    size_t length = len;
    int ret;
    unsigned long period;

    if (length > BUFF_SIZE)
        length = BUFF_SIZE;
    
    ret = kstrtoul_from_user(buf, len, 10, &period);
    if (ret) {
        pr_info("ko, error code is: %d\n", ret);
        return ret;
    } else {
        pr_info("ok, period is set to: %lu ms\n", period);
        blink_period_ms = period;
    }

    return length;
}

///////////////////////////////////////////////////////////////////////////////
// Function called when a read is done 
///////////////////////////////////////////////////////////////////////////////
static ssize_t my_read(struct file *fp, char __user *buf, size_t sz, loff_t *pOff)
{
    memset(kernel_buf, '\0', sizeof(kernel_buf));
    sprintf(kernel_buf, "Blink period is to %d ms\n", blink_period_ms);

    return simple_read_from_buffer(buf, sz, pOff, kernel_buf, BUFF_SIZE);
}  

///////////////////////////////////////////////////////////////////////////////
// Custom, read, write, open, close implementation
///////////////////////////////////////////////////////////////////////////////
static const struct file_operations sample_fops = {
    .owner			= THIS_MODULE,
    .write			= my_write,
    .read           = my_read,
    .open			= my_open,
    .release		= my_close,
};

///////////////////////////////////////////////////////////////////////////////
// Own device declaration
///////////////////////////////////////////////////////////////////////////////
struct miscdevice sample_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "gpio_ctrl_driver", ///< The device name in /dev
    .fops = &sample_fops,
};

///////////////////////////////////////////////////////////////////////////////
// Function called module is inserted
///////////////////////////////////////////////////////////////////////////////
static int __init gpio_ctrl_init(void)
{
    int error;

    pr_info("GPIO control: initialization\n");

    error = misc_register(&sample_device);
    if (error) {
        pr_err("can't misc_register :(\n");
        return error;
    }

    gpio_request(GPIO_CTRL_OUT, "sysfs");
    gpio_direction_output(GPIO_CTRL_OUT, true);    // Set the gpio to be in output mode and value at true
    gpio_export(GPIO_CTRL_OUT, false);             // Causes to appear in /sys/class/gpio
    gpio_set_value(GPIO_CTRL_OUT, 1);

    // Configure the task
    task = kthread_run(flash, NULL, "LED_flash_thread");
    if(IS_ERR(task)){
        pr_err("Failed to create the Led task\n");
        return PTR_ERR(task);
    }

    pr_info("GPIO control: End of initialization\n");
    
    return 0;
}

///////////////////////////////////////////////////////////////////////////////
// Function called module is exited
///////////////////////////////////////////////////////////////////////////////
static void __exit gpio_ctrl_exit(void)
{
    pr_info("GPIO control: Exit\n");
    misc_deregister(&sample_device);
    kthread_stop(task);
    gpio_set_value(GPIO_CTRL_OUT, 0);
    gpio_unexport(GPIO_CTRL_OUT);
    gpio_free(GPIO_CTRL_OUT);
}

module_init(gpio_ctrl_init)
module_exit(gpio_ctrl_exit)

