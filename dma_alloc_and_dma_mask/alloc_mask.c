#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");

struct my_device {
    struct platform_device *pdev;
    dma_addr_t dma_handle;
    void *virt_addr;
};

static int my_device_probe(struct platform_device *pdev)
{
    struct my_device *dev;
    struct resource *res;
    int ret;

    /* Allocate memory for the device */
    dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev) {
        dev_err(&pdev->dev, "Failed to allocate memory for device\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "**************good devm_kzalloc***************************\n");

    /* Get the memory resources for the device */
    res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!res) {
        dev_err(&pdev->dev, "Failed to get memory resource\n");
        return -ENODEV;
    }

    printk(KERN_INFO "**************good platform_get_resource***************************\n");

    /* Map the device memory into kernel virtual address space */
    dev->virt_addr = devm_ioremap_resource(&pdev->dev, res);
    if (IS_ERR(dev->virt_addr)) {
        dev_err(&pdev->dev, "Failed to map memory resource\n");
        return PTR_ERR(dev->virt_addr);
    }

    printk(KERN_INFO "**************good devm_ioremap_resource***************************\n");

    /* Set the DMA mask for the device */
    ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
    if (ret) {
        dev_err(&pdev->dev, "Failed to set DMA mask\n");
        return ret;
    }

    printk(KERN_INFO "**************good dma_set_mask_and_coherent***************************\n");

    /* Allocate coherent memory for DMA transfers */
    dev->virt_addr = dma_alloc_coherent(&pdev->dev, PAGE_SIZE, &dev->dma_handle, GFP_KERNEL);
    if (!dev->virt_addr) {
        dev_err(&pdev->dev, "Failed to allocate DMA memory\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "**************good dma_alloc_coherent***************************\n");

    /* Store the device pointer and DMA handle */
    dev->pdev = pdev;

    /* ... continue with device initialization ... */

    return 0;
}

static int my_device_remove(struct platform_device *pdev)
{
    struct my_device *dev = platform_get_drvdata(pdev);

    /* Free the coherent DMA memory */
    dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->virt_addr, dev->dma_handle);

    /* ... continue with device removal ... */

    return 0;
}

static struct platform_driver my_device_driver = {
        .probe = my_device_probe,
        .remove = my_device_remove,
        .driver = {
                .name = "my_own_device",
        },
};

module_platform_driver(my_device_driver);