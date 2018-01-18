#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>          

#include <asm/io.h>
#include <linux/delay.h>

MODULE_LICENSE("GPL");

#define DIR_REG_OFFSET 0x20a4004
#define DATA_REG_OFFSET 0x20a4000

static int hello_init(void)
{
	void *dir_reg, *data_reg;
	int dir_val, data_val;
	int i;

    	printk(KERN_ALERT "Hello, world\n");
	/* Remap the Addresses */
	dir_reg = ioremap(DIR_REG_OFFSET, 4);
	data_reg = ioremap(DATA_REG_OFFSET, 4);

	/* Read the existing values */
	dir_val = readl(dir_reg);
	data_val = readl(data_reg);

	/* Set GPIO3_27 as output */
	dir_val = dir_val | (1 << 27);
	writel(dir_val, dir_reg);

	/* Toggle LED 10 times */
	for (i = 0; i <= 10; ++i) {
		if (i % 2) {
			data_val = data_val | (1 << 27);
			writel(data_val, data_reg);
		} else {
			data_val = data_val & ~(1 << 27);
			writel(data_val, data_reg);
		}
		msleep(1000);
	}
	
	/*A non 0 return means init_module failed; module can't be loaded. */
    return 0;
}
static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);
