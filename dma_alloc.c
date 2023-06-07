#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/dma-mapping.h>
#include <linux/device.h>



//#define PAGE_SIZE 1024  // 1 kiB
#define BUFFER_SIZE 64

static struct dma_alloc_handle *dma_handle;
static char *dma_buffer;
static dma_addr_t dma_addr;

static int __init dma_alloc_init(void)
{
    //int ret;

    /* Allocate DMA-safe memory */
    dma_buffer = dma_alloc_coherent(NULL, BUFFER_SIZE, &dma_addr, GFP_DMA);
    if (!dma_buffer) {
        printk(KERN_ERR "Failed to allocate DMA buffer\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "DMA_____Buffer allocated well\n");
   // printk(KERN_INFO "Allocated memory at address: %p\n", dma_buffer);
    /* Use the DMA buffer here */

    return 0;
}

static void __exit dma_alloc_exit(void)
{
    /* Free the DMA-safe memory */
    printk(KERN_INFO "DMA______Good bye\n");
    dma_free_coherent(NULL, BUFFER_SIZE, dma_buffer, dma_addr);
}

module_init(dma_alloc_init);
module_exit(dma_alloc_exit);
MODULE_AUTHOR("Yannick");
MODULE_DESCRIPTION("DMA allocation");
MODULE_LICENSE("GPL v2");
