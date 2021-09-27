#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "userprog/pagedir.h"
#include "threads/interrupt.h"
#include "threads/palloc.h"
#include "threads/thread.h"
#include "page.h"
#include "threads/vaddr.h"

void stack_growth (struct thread *cur, const void* fault_addr){
	void *upage = pg_round_down(fault_addr);
	void *kpage = palloc_get_page(PAL_USER);
	pagedir_get_page(cur->pagedir, upage);
	pagedir_set_page(cur->pagedir, upage,kpage, true);

}
