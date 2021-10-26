/* anon.c: Implementation of page for non-disk image (a.k.a. anonymous page). */

#include "vm/vm.h"
#include "devices/disk.h"
#include "bitmap.h"
#include "threads/vaddr.h"

#define INVALID_SLOT_IDX SIZE_MAX

/* DO NOT MODIFY BELOW LINE */
static struct disk *swap_disk;
static bool anon_swap_in (struct page *page, void *kva);
static bool anon_swap_out (struct page *page);
static void anon_destroy (struct page *page);

//! ADD
struct bitmap *swap_table;
const size_t SECTORS_PER_PAGE = PGSIZE / DISK_SECTOR_SIZE;
//! END


/* DO NOT MODIFY this struct */
static const struct page_operations anon_ops = {
	.swap_in = anon_swap_in,
	.swap_out = anon_swap_out,
	.destroy = anon_destroy,
	.type = VM_ANON,
};

/* Initialize the data for anonymous pages */
/*Initialize for anonymous page subsystem. 
In this function, you can setup anything related to the anonymous page.ㄴ*/
void
vm_anon_init (void) {
	/* TODO: Set up the swap_disk. */
	swap_disk = disk_get(1, 1);
    size_t swap_size = disk_size(swap_disk) / SECTORS_PER_PAGE;
    swap_table = bitmap_create(swap_size);
}

/* Initialize the file mapping */
bool
anon_initializer (struct page *page, enum vm_type type, void *kva) {
	/* Set up the handler */
	page->operations = &anon_ops;
	// if (type & VM_STACK) page->operations = &anon_stack_ops;
	struct anon_page *anon_page = &page->anon;
	anon_page->owner = thread_current ();
	anon_page->swap_slot_idx = INVALID_SLOT_IDX;
	return true;
}

/* Swap in the page by read contents from the swap disk. */
static bool
anon_swap_in (struct page *page, void *kva) {
	struct anon_page *anon_page = &page->anon;
	if (anon_page->swap_slot_idx == INVALID_SLOT_IDX) return false;

	disk_sector_t sec_no;
	// Read page from disk with sector size chunk
	for (int i = 0; i < SECTORS_PER_PAGE; i++) {
		// convert swap slot index to reading sector number
		sec_no = (disk_sector_t) (anon_page->swap_slot_idx * SECTORS_PER_PAGE) + i;
		off_t ofs = i * DISK_SECTOR_SIZE;
		disk_read (swap_disk, sec_no, kva+ofs);   // swap_disk의 sec_no sector -> kva+ofs 에 copy
	}
	// Clear swap table
	bitmap_set (swap_table, anon_page->swap_slot_idx, false);

	anon_page->swap_slot_idx = INVALID_SLOT_IDX;

	return true;
}

/* Swap out the page by writing contents to the swap disk. */
static bool
anon_swap_out (struct page *page) {
	struct anon_page *anon_page = &page->anon;

		// Get swap slot index from swap table
	size_t swap_slot_idx = bitmap_scan_and_flip (swap_table, 0, 1, false);
	if (swap_slot_idx == BITMAP_ERROR)
		PANIC("There is no free swap slot!");

	// Copy page frame content to swap_slot
	if (page == NULL || page->frame == NULL || page->frame->kva == NULL)
		return false;

	disk_sector_t sec_no;
	// Write page to disk with sector size chunk
	for (int i = 0; i < SECTORS_PER_PAGE; i++) {
		// convert swap slot index to writing sector number
		sec_no = (disk_sector_t) (swap_slot_idx * SECTORS_PER_PAGE) + i;
		off_t ofs = i * DISK_SECTOR_SIZE;
		disk_write (swap_disk, sec_no, page->frame->kva + ofs);
	}
	anon_page->swap_slot_idx = swap_slot_idx;

	// Set "not present" to page, and clear.
	pml4_clear_page (anon_page->owner->pml4, page->va);
	pml4_set_dirty (anon_page->owner->pml4, page->va, false);
	page->frame = NULL;

	return true;
}

/* Destroy the anonymous page. PAGE will be freed by the caller. */
static void
anon_destroy (struct page *page) {
	if (page -> frame!= NULL){
		list_remove (&page->frame->elem);
		free(page->frame);
	}
	else {
		// Swapped anon page case
		struct anon_page *anon_page = &page->anon;
		ASSERT (anon_page->swap_slot_idx != INVALID_SLOT_IDX);

		// Clear swap table
		bitmap_set (swap_table, anon_page->swap_slot_idx, false);
	}
}
