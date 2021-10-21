/* vm.c: Generic interface for virtual memory objects. */

#include "threads/malloc.h"
#include "vm/vm.h"
#include "vm/inspect.h"
#include "threads/vaddr.h"

/* Initializes the virtual memory subsystem by invoking each subsystem's
 * intialize codes. */
void
vm_init (void) {
	vm_anon_init ();
	vm_file_init ();
#ifdef EFILESYS  /* For project 4 */
	pagecache_init ();
#endif
	register_inspect_intr ();
	/* DO NOT MODIFY UPPER LINES. */
	/* TODO: Your code goes here. */
}

/* Get the type of the page. This function is useful if you want to know the
 * type of the page after it will be initialized.
 * This function is fully implemented now. */
enum vm_type
page_get_type (struct page *page) {
	int ty = VM_TYPE (page->operations->type);
	switch (ty) {
		case VM_UNINIT:
			return VM_TYPE (page->uninit.type);
		default:
			return ty;
	}
}

/* Helpers */
static struct frame *vm_get_victim (void);
static bool vm_do_claim_page (struct page *page);
static struct frame *vm_evict_frame (void);

/* Create the pending page object with initializer. If you want to create a
 * page, do not create it directly and make it through this function or
 * `vm_alloc_page`. */
bool
vm_alloc_page_with_initializer (enum vm_type type, void *upage, bool writable,
		vm_initializer *init, void *aux) {

	ASSERT (VM_TYPE(type) != VM_UNINIT)

	struct supplemental_page_table *spt = &thread_current ()->spt;

	/* Check wheter the upage is already occupied or not. */
	if (spt_find_page (spt, upage) == NULL) {
		/* TODO: Create the page, fetch the initialier according to the VM type,
		 * TODO: and then create "uninit" page struct by calling uninit_new. You
		 * TODO: should modify the field after calling the uninit_new. */
		struct page* page = malloc(sizeof (struct page));
		if (VM_TYPE(type) == VM_ANON){
			uninit_new (page, upage, init, type, aux, anon_initializer);
		}
		// else if (VM_TYPE(type) == VM_FILE){
		// 	uninit_new (page, upage, init, type, aux, file_backed_initializer);
		// }
		page->writable = writable;
		/* TODO: Insert the page into the spt. */
		spt_insert_page (spt, page);
		return true;
	}
	return false;
}

/* Find VA from spt and return page. On error, return NULL. */
struct page *  /*page 구조체 pointer로 변경해보기*/ 
spt_find_page (struct supplemental_page_table *spt, void *va) {
	struct page page;
	page.va = pg_round_down (va);
	struct hash_elem *e = hash_find (spt -> page_table, &page.hash_elem);
	if (e == NULL) return NULL;
	struct page* result = hash_entry (e, struct page, hash_elem);
	ASSERT((va < result -> va + PGSIZE) && va >= result -> va);
	return result;
}

/* Insert PAGE into spt with validation. */
bool
spt_insert_page (struct supplemental_page_table *spt,
		struct page *page) {
	/* TODO: Fill this function. */
	struct hash_elem *result= hash_insert (spt -> page_table, &page -> hash_elem);
	return (result == NULL) ? true : false ;
}

void
spt_remove_page (struct supplemental_page_table *spt, struct page *page) {
	struct hash_elem* e = hash_delete (spt -> page_table, &page ->hash_elem);
	if (e != NULL) vm_dealloc_page (page);
	return true;
}

/* Get the struct frame, that will be evicted. */
static struct frame *
vm_get_victim (void) {
	struct frame *victim = NULL;
	 /* TODO: The policy for eviction is up to you. */

	return victim;
}

/* Evict one page and return the corresponding frame.
 * Return NULL on error.*/
static struct frame *
vm_evict_frame (void) {
	struct frame *victim UNUSED = vm_get_victim ();
	/* TODO: swap out the victim and return the evicted frame. */

	return NULL;
}

/* palloc() and get frame. If there is no available page, evict the page
 * and return it. This always return valid address. That is, if the user pool
 * memory is full, this function evicts the frame to get the available memory
 * space.*/
/*  Gets a new physical page from the user pool by calling palloc_get_page. 
	When successfully got a page from the user pool, also allocates a frame, initialize its members, and returns it. 
	After you implement vm_get_frame, you have to allocate all user space pages (PALLOC_USER) through this function. 
	You don't need to handle swap out for now in case of page allocation failure. 
	Just mark those case with PANIC ("todo") for now.*/


static struct frame *
vm_get_frame (void) {
	struct frame * frame = malloc (sizeof (struct frame));
	frame -> kva = palloc_get_page (PAL_USER);
	frame -> page = NULL;
	ASSERT (frame != NULL);
	ASSERT (frame->page == NULL);
	// Add swap case handling
	// if (frame->kva == NULL) {
	//   free (frame);
	//   frame = vm_evict_frame ();
	// }
	ASSERT (frame->kva != NULL);
	return frame;
}

/* Growing the stack. */
static void
vm_stack_growth (void *addr UNUSED) {
	void *stack_bottom = pg_round_down (addr);
	size_t req_stack_size = USER_STACK - (uintptr_t)stack_bottom;
	if (req_stack_size > (1 << 20)) PANIC("Stack limit exceeded!\n"); // 1MB

	// Alloc page from tested region to previous claimed stack page.
	void *growing_stack_bottom = stack_bottom;
	while ((uintptr_t) growing_stack_bottom < USER_STACK &&
		vm_alloc_page (VM_ANON | VM_MARKER_0, growing_stack_bottom, true)) {
	      growing_stack_bottom += PGSIZE;
	};
	vm_claim_page (stack_bottom); // Lazy load requested stack page only
}

/* Handle the fault on write_protected page */
static bool
vm_handle_wp (struct page *page UNUSED) {
	return false;
}

// /* Return true on success */
bool
vm_try_handle_fault (struct intr_frame *f UNUSED, void *addr,
		bool user, bool write, bool not_present) {
	struct thread *curr = thread_current ();
	struct supplemental_page_table *spt = &curr->spt;
	/* Validate the fault */
	if (is_kernel_vaddr (addr) && user) return false;
	void *stack_bottom = pg_round_down (curr->rsp);
	if (write && (stack_bottom - PGSIZE <= addr &&
	      (uintptr_t) addr < USER_STACK)) {
	  /* Allow stack growth writing below single PGSIZE range
	   * of current stack bottom inferred from stack pointer. */
	  vm_stack_growth (addr);
	  return true;
	}
	struct page* page = spt_find_page (spt, addr);
	if (page == NULL) return false;
	if (write && !not_present) return vm_handle_wp (page); /*존재하는 페이지에 대한 쓰기 접근*/
	return vm_do_claim_page (page);
}
// bool
// vm_try_handle_fault (struct intr_frame *f UNUSED, void *addr UNUSED,
// 		bool user UNUSED, bool write UNUSED, bool not_present UNUSED) {
// 	struct supplemental_page_table *spt UNUSED = &thread_current ()->spt;
// 	struct page *page = NULL;
// 	/* TODO: Validate the fault */


// 	/* TODO: Your code goes here */

// 	return vm_do_claim_page (page);
// }

/* Free the page.
 * DO NOT MODIFY THIS FUNCTION. */
void
vm_dealloc_page (struct page *page) {
	destroy (page);
	free (page);
}

/* Claim the page that allocate on VA. */
/*Claims the page to allocate va. 
  You will first need to get a page and then calls vm_do_claim_page with the page.*/
  /*spt_find_page : Find struct page that corresponds to va from the given supplemental page table. If fail, return NULL.*/
bool
vm_claim_page (void *va UNUSED) {
	struct page *page = spt_find_page (&thread_current () ->spt, va);
	if (page == NULL) return false;
	return vm_do_claim_page (page);
}

/* Claim the PAGE and set up the mmu. */
/*Claims, meaning allocate a physical frame, a page. 
You first get a frame by calling vm_get_frame (which is already done for you in the template). 
Then, you need to set up the MMU. In other words, add the mapping from the virtual address to the physical address in the page table. 
The return value should indicate whether the operation was successful or not.*/
static bool
vm_do_claim_page (struct page *page) {
	struct frame *frame = vm_get_frame ();  /*Physical address와의 connection*/
	struct thread *curr = thread_current ();

	ASSERT (frame != NULL);
	ASSERT (page != NULL);

	/* Set links */
	frame->page = page;
	page->frame = frame;

	/* TODO: Insert page table entry to map page's VA to frame's PA. */
	if (!pml4_set_page (curr -> pml4, page -> va, frame->kva, page -> writable))
		return false;
	return swap_in (page, frame->kva);
}

static uint64_t
page_hash (const struct hash_elem *p_, void *aux UNUSED) {
  const struct page *p = hash_entry (p_, struct page, hash_elem);
  return hash_bytes (&p->va, sizeof p->va);
}

static bool
page_less (const struct hash_elem *a_,
           const struct hash_elem *b_, void *aux UNUSED) {
  const struct page *a = hash_entry (a_, struct page, hash_elem);
  const struct page *b = hash_entry (b_, struct page, hash_elem);

  return a->va < b->va;
}

/*Initializes the supplemental page table. 
  You may choose the data structure to use for the supplemental page table. 
  The function is called when a new process starts (in initd of userprog/process.c) 
  and when a process is being forked (in __do_fork of userprog/process.c)*/
void
supplemental_page_table_init (struct supplemental_page_table *spt UNUSED) {
	struct hash* page_table = malloc(sizeof (struct hash));
	hash_init (page_table, page_hash, page_less, NULL);
	spt -> page_table = page_table;
}

/* Copy supplemental page table from src to dst */
/*Find struct page that corresponds to va from the given supplemental page table. 
  If fail, return NULL.*/
bool
supplemental_page_table_copy (struct supplemental_page_table *dst UNUSED,
		struct supplemental_page_table *src UNUSED) {
			/*Iterate Source spt hash table*/
	struct hash_iterator i;
	hash_first (&i, src -> page_table);
	while (hash_next (&i)) {
		struct page *page = hash_entry (hash_cur (&i), struct page, hash_elem);
		/*Handle UNINIT page*/
		if (page -> operations -> type == VM_UNINIT){
			vm_initializer* init = page ->uninit.init;
			bool writable = page -> writable;
			int type = page ->uninit.type;
			void* aux = page ->uninit.aux;
			if (type & VM_ANON){
				vm_alloc_page_with_initializer (type, page -> va, writable, init, (void*) aux);
			}
			else if (type & VM_FILE){
				//Do_nothing(it should not inherit mmap)
			}
		}
		/* Handle ANON/FILE page*/
		else if (page_get_type(page) == VM_ANON){
			if (!vm_alloc_page (page -> operations -> type, page -> va, page -> writable))
				return false;
			struct page* new_page = spt_find_page (&thread_current () -> spt, page -> va);
			if (!vm_do_claim_page (new_page))
				return false;
			memcpy (new_page -> frame -> kva, page -> frame -> kva, PGSIZE);
		}
		else if (page_get_type(page) == VM_FILE){
			//Do nothing(it should not inherit mmap)
		}
	}
	return true;

}

/* Free the resource hold by the supplemental page table */
/*Insert struct page into the given supplemental page table. 
This function should checks that the virtual address does not exist in the given supplemental page table.*/
void
supplemental_page_table_kill (struct supplemental_page_table *spt UNUSED) {
	/* TODO: Destroy all the supplemental_page_table hold by thread and
	 * TODO: writeback all the modified contents to the storage. */
	/*나중에 구현할래*/
}
