#include <linux/module.h>
#include <linux/dmaengine.h>

static int __init my_dma_init(void)
{
    struct dma_chan *dma_chan;
    struct scatterlist sg;
    struct dma_async_tx_descriptor *desc;
    dma_cookie_t cookie;
    int ret;

    printk("Finding a chanel 0\n");

    /* Get a DMA channel */
    dma_chan = dma_request_chan(NULL, "dma0");
    if (IS_ERR(dma_chan)) {
        printk("Failed to request DMA channel\n");
        return PTR_ERR(dma_chan);
    }

    printk("--------Great the channel is available------------\n");


    /* Prepare DMA transfer */
    sg_init_one(&sg, kmalloc(4096, GFP_KERNEL), 4096);
    desc = dmaengine_prep_slave_sg(dma_chan, &sg, 1, DMA_DEV_TO_MEM, DMA_PREP_INTERRUPT);
    if (!desc) {
        printk("Failed to prepare DMA transfer\n");
        ret = -ENOMEM;
        goto err_dma_release;
    }

    /* Submit DMA transfer */
    cookie = dmaengine_submit(desc);
    if (dma_submit_error(cookie)) {
        printk("Failed to submit DMA transfer\n");
        ret = -EIO;
        goto err_dma_release;
    }

    /* Wait for DMA transfer to complete */
    dma_async_issue_pending(dma_chan);
    ret = dma_sync_wait(dma_chan, cookie);
    if (ret) {
        printk("Failed to wait for DMA transfer\n");
        goto err_dma_release;
    }

    /* Use DMA buffer */

    dma_release_channel(dma_chan);

    return 0;

    err_dma_release:
    dma_release_channel(dma_chan);
    return ret;
}

static void __exit my_dma_exit(void)
{
    printk(KERN_INFO "**************good bye***************************\n");}

module_init(my_dma_init);
module_exit(my_dma_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Example DMA module");