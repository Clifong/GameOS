#include "multiboot2.h"
#include <stdint.h>

/* Multiboot 2, unlike the original specification, uses tags
*  to organize its contents. Each tag has an associated type,
*  represented by a 32-bit integer. This function finds a tag
*  given its type. */
struct multiboot_tag *multiboot_find_tag(void *mbd, uint32_t type) {
    /* The multiboot info structure begins with a 32-bit integer
    *  indicating the total size of the structure. This is then
    *  followed by a 32-bit reserved region and then by the tags. */
	struct multiboot_tag *tag = (void *)mbd + 8;
	while ((void *)tag < (void *)mbd + *((uint32_t *)mbd)) {
		if (tag->type == type) {
			return tag;
		}
		tag = (void *)tag + tag->size;
		/* Tags are always aligned on 8-byte boundaries. */
		if ((uintptr_t)tag % 8 > 0) {
			tag = (void *)tag + 8 - ((uintptr_t)tag % 8);
		}
	}
	return 0;
}


void _main(void *mbd, uint32_t magic)
{
    if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
        panic("invalid magic number!");
    }
    
    struct multiboot_tag_mmap *tag_mmap =
	    (struct multiboot_tag_mmap *)multiboot_find_tag(
		multiboot, MULTIBOOT_TAG_TYPE_MMAP);

	if (!tag_mmap) {
		panic("No memory map tag found!\n");
	}

	struct multiboot_mmap_entry *entry =
	    (struct multiboot_mmap_entry *)(uintptr_t)tag_mmap->entries;
	while ((void *)entry < (void *)tag_mmap + tag_mmap->size) {
		kprintf("Start Addr: %x | Length: %x | Type: %i.\n",
		    entry->addr, entry->len, entry->type);
		entry = (void *)entry + tag_mmap->entry_size;
	}

}