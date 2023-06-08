#include <linux/dma-mapping.h>
#include <linux/dmapool.h>

/* Définir la taille et l'alignement du tampon */
#define BUFFER_SIZE 4096
#define BUFFER_ALIGN 4

/* Définir une structure pour stocker les informations sur le pool DMA */
struct my_device {
    struct dma_pool *pool;
    dma_addr_t dma_addr;
    void *buffer;
};

static struct dma_pool *pool;

/* Initialiser le périphérique */
static int __init my_device_init(void)
{
    struct my_device *dev = NULL;

    printk(KERN_INFO "Initiate the load dma_pool_create................\n\n");

    /* Créer un pool de mémoire tampon DMA pour le périphérique */
    pool = dma_pool_create("my_device", NULL, BUFFER_SIZE, BUFFER_ALIGN, 0);
    if (!dev->pool) {
        printk(KERN_ERR "Failed to create DMA pool\n");
        return -ENOMEM;
    }

    printk(KERN_INFO "allocation okay ................\n\n");

    /* Allouer un tampon de mémoire à partir du pool */
    /*dev->buffer = dma_pool_alloc(dev->pool, GFP_KERNEL, &dev->dma_addr);
    if (!dev->buffer) {
        printk(KERN_ERR "Failed to allocate DMA buffer\n");
        dma_pool_destroy(dev->pool);
        return -ENOMEM;
    }
*/
    /* Utiliser le tampon alloué pour les transferts DMA */
    /* ... */

    return 0;
}

/* Libérer les ressources du périphérique */
static void __exit my_device_exit(void)
{
    printk(KERN_INFO "exit dma_pool_create................\n\n");
    /* Libérer le tampon de mémoire */
    /*if (dev->buffer) {
        dma_pool_free(dev->pool, dev->buffer, dev->dma_addr);
    }*/

    /* Détruire le pool de mémoire tampon DMA */
    /*if (dev->pool) {
        dma_pool_destroy(dev->pool);
    }*/
}

module_init(my_device_init);
module_exit(my_device_exit);

MODULE_LICENSE("GPL");