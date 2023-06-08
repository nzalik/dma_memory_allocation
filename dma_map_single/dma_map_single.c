#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>

MODULE_LICENSE("GPL");

struct my_device {
    struct device *dev;
    dma_addr_t dma_handle;
    void *buffer;
};

static int __init my_device_init(void)
{
    printk(KERN_INFO "Initiate the load................\n\n");
    struct my_device *my_dev;
    size_t size = 4096;
    gfp_t gfp_flags = GFP_KERNEL;

    my_dev = kzalloc(sizeof(*my_dev), GFP_KERNEL);
    if (!my_dev)
        return -ENOMEM;

    printk(KERN_INFO "Successfully allocate with kmalloc................\n\n");
    //my_dev->dev = device_create(NULL, NULL, 0, NULL, "my_device");
//    if (IS_ERR(my_dev->dev)) {
//        kfree(my_dev);
//        return PTR_ERR(my_dev->dev);
//    }

    printk(KERN_INFO "Starting to map memory inside device driver................ %p \n\n", my_dev);
    my_dev->buffer = dma_alloc_attrs(my_dev->dev, size, &my_dev->dma_handle, gfp_flags, NULL);
    if (!my_dev->buffer) {
        device_destroy(NULL, 0);
        kfree(my_dev);
        return -ENOMEM;
    }

    /* Use the DMA buffer... */

    printk(KERN_INFO "Successfully map the memory inside the driver memory................%p \n\n",my_dev->buffer);
    dma_free_attrs(my_dev->dev, size, my_dev->buffer, my_dev->dma_handle, NULL);
    device_destroy(NULL, 0);
    kfree(my_dev);

    printk(KERN_INFO "Good bye bye................\n\n");
    return 0;
}

static void __exit my_device_exit(void)
{
    printk(KERN_INFO "Outside outside ................\n\n");
}

module_init(my_device_init);
module_exit(my_device_exit);