[1mdiff --git a/vm/build/kernel.o b/vm/build/kernel.o[m
[1mindex 3ecab56..7c463fd 100755[m
Binary files a/vm/build/kernel.o and b/vm/build/kernel.o differ
[1mdiff --git a/vm/build/results b/vm/build/results[m
[1mdeleted file mode 100644[m
[1mindex 6960f1d..0000000[m
[1m--- a/vm/build/results[m
[1m+++ /dev/null[m
[36m@@ -1,141 +0,0 @@[m
[31m-pass tests/userprog/args-none[m
[31m-pass tests/userprog/args-single[m
[31m-pass tests/userprog/args-multiple[m
[31m-pass tests/userprog/args-many[m
[31m-pass tests/userprog/args-dbl-space[m
[31m-pass tests/userprog/halt[m
[31m-pass tests/userprog/exit[m
[31m-pass tests/userprog/create-normal[m
[31m-pass tests/userprog/create-empty[m
[31m-pass tests/userprog/create-null[m
[31m-pass tests/userprog/create-bad-ptr[m
[31m-pass tests/userprog/create-long[m
[31m-pass tests/userprog/create-exists[m
[31m-pass tests/userprog/create-bound[m
[31m-pass tests/userprog/open-normal[m
[31m-pass tests/userprog/open-missing[m
[31m-pass tests/userprog/open-boundary[m
[31m-pass tests/userprog/open-empty[m
[31m-pass tests/userprog/open-null[m
[31m-pass tests/userprog/open-bad-ptr[m
[31m-pass tests/userprog/open-twice[m
[31m-pass tests/userprog/close-normal[m
[31m-pass tests/userprog/close-twice[m
[31m-pass tests/userprog/close-bad-fd[m
[31m-pass tests/userprog/read-normal[m
[31m-pass tests/userprog/read-bad-ptr[m
[31m-FAIL tests/userprog/read-boundary[m
[31m-pass tests/userprog/read-zero[m
[31m-pass tests/userprog/read-stdout[m
[31m-pass tests/userprog/read-bad-fd[m
[31m-pass tests/userprog/write-normal[m
[31m-pass tests/userprog/write-bad-ptr[m
[31m-pass tests/userprog/write-boundary[m
[31m-pass tests/userprog/write-zero[m
[31m-pass tests/userprog/write-stdin[m
[31m-pass tests/userprog/write-bad-fd[m
[31m-FAIL tests/userprog/fork-once[m
[31m-FAIL tests/userprog/fork-multiple[m
[31m-FAIL tests/userprog/fork-recursive[m
[31m-FAIL tests/userprog/fork-read[m
[31m-FAIL tests/userprog/fork-close[m
[31m-FAIL tests/userprog/fork-boundary[m
[31m-FAIL tests/userprog/exec-once[m
[31m-FAIL tests/userprog/exec-arg[m
[31m-FAIL tests/userprog/exec-boundary[m
[31m-pass tests/userprog/exec-missing[m
[31m-pass tests/userprog/exec-bad-ptr[m
[31m-FAIL tests/userprog/exec-read[m
[31m-FAIL tests/userprog/wait-simple[m
[31m-FAIL tests/userprog/wait-twice[m
[31m-FAIL tests/userprog/wait-killed[m
[31m-pass tests/userprog/wait-bad-pid[m
[31m-FAIL tests/userprog/multi-recurse[m
[31m-FAIL tests/userprog/multi-child-fd[m
[31m-pass tests/userprog/rox-simple[m
[31m-FAIL tests/userprog/rox-child[m
[31m-FAIL tests/userprog/rox-multichild[m
[31m-pass tests/userprog/bad-read[m
[31m-pass tests/userprog/bad-write[m
[31m-pass tests/userprog/bad-read2[m
[31m-pass tests/userprog/bad-write2[m
[31m-pass tests/userprog/bad-jump[m
[31m-pass tests/userprog/bad-jump2[m
[31m-FAIL tests/vm/pt-grow-stack[m
[31m-pass tests/vm/pt-grow-bad[m
[31m-FAIL tests/vm/pt-big-stk-obj[m
[31m-pass tests/vm/pt-bad-addr[m
[31m-pass tests/vm/pt-bad-read[m
[31m-FAIL tests/vm/pt-write-code[m
[31m-FAIL tests/vm/pt-write-code2[m
[31m-FAIL tests/vm/pt-grow-stk-sc[m
[31m-pass tests/vm/page-linear[m
[31m-FAIL tests/vm/page-parallel[m
[31m-FAIL tests/vm/page-merge-seq[m
[31m-FAIL tests/vm/page-merge-par[m
[31m-FAIL tests/vm/page-merge-stk[m
[31m-FAIL tests/vm/page-merge-mm[m
[31m-pass tests/vm/page-shuffle[m
[31m-FAIL tests/vm/mmap-read[m
[31m-FAIL tests/vm/mmap-close[m
[31m-FAIL tests/vm/mmap-unmap[m
[31m-FAIL tests/vm/mmap-overlap[m
[31m-FAIL tests/vm/mmap-twice[m
[31m-FAIL tests/vm/mmap-write[m
[31m-FAIL tests/vm/mmap-ro[m
[31m-FAIL tests/vm/mmap-exit[m
[31m-FAIL tests/vm/mmap-shuffle[m
[31m-pass tests/vm/mmap-bad-fd[m
[31m-FAIL tests/vm/mmap-clean[m
[31m-FAIL tests/vm/mmap-inherit[m
[31m-FAIL tests/vm/mmap-misalign[m
[31m-FAIL tests/vm/mmap-null[m
[31m-FAIL tests/vm/mmap-over-code[m
[31m-FAIL tests/vm/mmap-over-data[m
[31m-FAIL tests/vm/mmap-over-stk[m
[31m-FAIL tests/vm/mmap-remove[m
[31m-pass tests/vm/mmap-zero[m
[31m-pass tests/vm/mmap-bad-fd2[m
[31m-pass tests/vm/mmap-bad-fd3[m
[31m-pass tests/vm/mmap-zero-len[m
[31m-FAIL tests/vm/mmap-off[m
[31m-FAIL tests/vm/mmap-bad-off[m
[31m-FAIL tests/vm/mmap-kernel[m
[31m-FAIL tests/vm/lazy-file[m
[31m-pass tests/vm/lazy-anon[m
[31m-FAIL tests/vm/swap-file[m
[31m-FAIL tests/vm/swap-anon[m
[31m-FAIL tests/vm/swap-iter[m
[31m-FAIL tests/vm/swap-fork[m
[31m-pass tests/filesys/base/lg-create[m
[31m-pass tests/filesys/base/lg-full[m
[31m-pass tests/filesys/base/lg-random[m
[31m-pass tests/filesys/base/lg-seq-block[m
[31m-pass tests/filesys/base/lg-seq-random[m
[31m-pass tests/filesys/base/sm-create[m
[31m-pass tests/filesys/base/sm-full[m
[31m-pass tests/filesys/base/sm-random[m
[31m-pass tests/filesys/base/sm-seq-block[m
[31m-pass tests/filesys/base/sm-seq-random[m
[31m-FAIL tests/filesys/base/syn-read[m
[31m-pass tests/filesys/base/syn-remove[m
[31m-FAIL tests/filesys/base/syn-write[m
[31m-pass tests/threads/alarm-single[m
[31m-pass tests/threads/alarm-multiple[m
[31m-pass tests/threads/alarm-simultaneous[m
[31m-pass tests/threads/alarm-priority[m
[31m-pass tests/threads/alarm-zero[m
[31m-pass tests/threads/alarm-negative[m
[31m-pass tests/threads/priority-change[m
[31m-pass tests/threads/priority-donate-one[m
[31m-pass tests/threads/priority-donate-multiple[m
[31m-pass tests/threads/priority-donate-multiple2[m
[31m-pass tests/threads/priority-donate-nest[m
[31m-pass tests/threads/priority-donate-sema[m
[31m-pass tests/threads/priority-donate-lower[m
[31m-pass tests/threads/priority-fifo[m
[31m-pass tests/threads/priority-preempt[m
[31m-pass tests/threads/priority-sema[m
[31m-pass tests/threads/priority-condvar[m
[31m-pass tests/threads/priority-donate-chain[m
[31m-FAIL tests/vm/cow/cow-simple[m
[1mdiff --git a/vm/build/threads/intr-stubs.o b/vm/build/threads/intr-stubs.o[m
[1mindex c45aa0e..b7d14fc 100644[m
Binary files a/vm/build/threads/intr-stubs.o and b/vm/build/threads/intr-stubs.o differ
[1mdiff --git a/vm/build/threads/loader.o b/vm/build/threads/loader.o[m
[1mindex 98c775f..6bdba97 100644[m
Binary files a/vm/build/threads/loader.o and b/vm/build/threads/loader.o differ
[1mdiff --git a/vm/build/threads/start.o b/vm/build/threads/start.o[m
[1mindex cdb8873..1485721 100644[m
Binary files a/vm/build/threads/start.o and b/vm/build/threads/start.o differ
[1mdiff --git a/vm/build/userprog/syscall-entry.o b/vm/build/userprog/syscall-entry.o[m
[1mindex d7b2a9b..e51af5f 100644[m
Binary files a/vm/build/userprog/syscall-entry.o and b/vm/build/userprog/syscall-entry.o differ
[1mdiff --git a/vm/vm.c b/vm/vm.c[m
[1mindex c89188f..8199b89 100644[m
[1m--- a/vm/vm.c[m
[1m+++ b/vm/vm.c[m
[36m@@ -145,7 +145,6 @@[m [mvm_get_frame (void) {[m
 /* Growing the stack. */[m
 static void[m
 vm_stack_growth (void *addr UNUSED) {[m
[31m-printf("씨발\n");[m
 }[m
 [m
 /* Handle the fault on write_protected page */[m
[36m@@ -154,21 +153,24 @@[m [mvm_handle_wp (struct page *page UNUSED) {[m
 }[m
 [m
 // /* Return true on success */[m
[31m-bool[m
[31m-vm_try_handle_fault (struct intr_frame *f UNUSED, void *addr,[m
[31m-		bool user, bool write, bool not_present) {[m
[32m+[m[32mbool   /* addr : faulted address. */[m
[32m+[m[32mvm_try_handle_fault (struct intr_frame *f UNUSED, void *addr, bool user, bool write, bool not_present)[m[41m [m
[32m+[m[32m{[m
 	struct thread *curr = thread_current ();[m
 	struct supplemental_page_table *spt = &curr->spt;[m
 	/* Validate the fault */[m
[31m-	if (is_kernel_vaddr (addr) && user) return false;[m
[32m+[m	[32mif (is_kernel_vaddr (addr) && user)[m[41m [m
[32m+[m		[32mreturn false;[m
[32m+[m
 	void *stack_bottom = pg_round_down (curr->rsp);[m
[31m-	if (write && (stack_bottom - PGSIZE <= addr &&[m
[31m-	      (uintptr_t) addr < USER_STACK)) {[m
[32m+[m	[32mif (write && (stack_bottom - PGSIZE <= addr && (uintptr_t) addr < USER_STACK))[m[41m [m
[32m+[m	[32m{[m
 	  /* Allow stack growth writing below single PGSIZE range[m
 	   * of current stack bottom inferred from stack pointer. */[m
 	  vm_stack_growth (addr);[m
 	  return true;[m
 	}[m
[32m+[m
 	struct page* page = spt_find_page (spt, addr);[m
 	if (page == NULL) return false;[m
 	if (write && !not_present) return vm_handle_wp (page);[m
[36m@@ -196,7 +198,7 @@[m [mvm_dealloc_page (struct page *page) {[m
 }[m
 [m
 /* Claim the page that allocate on VA. */[m
[31m-/*Claims the page to allocate va. [m
[32m+[m[32m/*Claims the page to allocate va.[m
   You will first need to get a page and then calls vm_do_claim_page with the page.*/[m
   /*spt_find_page : Find struct page that corresponds to va from the given supplemental page table. If fail, return NULL.*/[m
 bool[m
[36m@@ -224,7 +226,7 @@[m [mvm_do_claim_page (struct page *page) {[m
 	page->frame = frame;[m
 [m
 	/* TODO: Insert page table entry to map page's VA to frame's PA. */[m
[31m-	if (!pml4_set_page (curr -> pml4, page -> va, frame->kva, page -> writable))[m
[32m+[m	[32mif (! (curr -> pml4, page -> va, frame->kva, page -> writable))[m
 		return false;[m
 	return swap_in (page, frame->kva);[m
 }[m
