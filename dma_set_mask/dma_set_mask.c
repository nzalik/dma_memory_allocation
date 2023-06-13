#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

struct my_sound_card *card;
struct device *dev;

static int __init my_dma_init(void)
{

    int err = 1;

    printk(KERN_INFO "**************Loading engine***************************\n");

    err = dma_set_mask_and_coherent(dev, DMA_BIT_MASK(64));
    if (err)
        dev_warn(dev, "Failed to set 64-bit DMA mask\n");

    printk(KERN_INFO "**************Good job***************************\n");

    return 0;
}

static void __exit my_dma_exit(void)
{
    printk(KERN_INFO "**************good bye***************************\n");
}

module_init(my_dma_init);
module_exit(my_dma_exit);