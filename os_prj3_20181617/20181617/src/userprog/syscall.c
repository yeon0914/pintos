#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include <string.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "threads/synch.h"

static void syscall_handler (struct intr_frame *);

void
syscall_init (void) 
{
	//lock_init(&file_lock);
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void user_vaddr(const void *vaddr){
	if(!is_user_vaddr(vaddr))
		sys_exit(-1);
}

static void
syscall_handler (struct intr_frame *f UNUSED) 
{
  //printf ("system call!\n");
  //printf("syscall num : %d\n", *(uint32_t*)(f->esp));
  
	switch(*(uint32_t*)(f->esp)){
		case SYS_HALT:
			//printf("halt\n");
			sys_halt();
			break;
		case SYS_EXIT:
			//printf("exit\n");
			user_vaddr(f->esp+4);

			sys_exit(*(uint32_t*)(f->esp+4));
			break;
		case SYS_EXEC :
			//printf("exec\n");
			user_vaddr(f->esp+4);
			f->eax = sys_exec((char*)*(uint32_t*)(f->esp+4));
			break;
		case SYS_WAIT :
			//printf("wait\n");
			user_vaddr(f->esp+4);
			f->eax = sys_wait(*(uint32_t*)(f->esp+4));
			break;
		case SYS_READ:
			//printf("read\n");
			f->eax = sys_read ((int)*(uint32_t*)(f->esp+4),(void*)*(uint32_t*)(f->esp+8),
					(unsigned)*(uint32_t*)(f->esp+12));
			break;
		case SYS_WRITE:
			//printf("write\n");
			f->eax = sys_write((int)*(uint32_t*)(f->esp+4), (const void*)*(uint32_t*)(f->esp+8),
					(unsigned)*(uint32_t*)(f->esp+12));
			break;
		case SYS_FIB:
			f->eax=sys_fibonacci((int)*(uint32_t*)(f->esp+4));
			break;
		case SYS_MAX:
			f->eax=sys_max_of_four_int((int)*(uint32_t*)(f->esp+4), (int)*(uint32_t*)(f->esp+8),
					(int)*(uint32_t*)(f->esp+12), (int)*(uint32_t*)(f->esp+16));
			break;
		case SYS_CREATE:
			user_vaddr(f->esp+4);
			user_vaddr(f->esp+8);
			f->eax = sys_create((const char*)*(uint32_t*)(f->esp+4), (unsigned)*(uint32_t*)(f->esp+8));
			break;
		case SYS_REMOVE:
			user_vaddr(f->esp+4);
			f->eax = sys_remove((const char*)*(uint32_t*)(f->esp+4));
			break;
		case SYS_OPEN:
			user_vaddr(f->esp+4);
			f->eax = sys_open((const char*)*(uint32_t*)(f->esp+4));
			break;
		case SYS_CLOSE:
			user_vaddr(f->esp+4);
			sys_close((int)*(uint32_t*)(f->esp+4));
			break;
		case SYS_FILESIZE:
			user_vaddr(f->esp+4);
			f->eax = sys_filesize((int)*(uint32_t*)(f->esp+4));
			break;
		case SYS_SEEK:
			user_vaddr(f->esp+4);
			user_vaddr(f->esp+8);
			sys_seek((int)*(uint32_t*)(f->esp+4), (unsigned)*(uint32_t*)(f->esp+8));
			break;
		case SYS_TELL:
			user_vaddr(f->esp+4);
			f->eax = sys_tell((int)*(uint32_t*)(f->esp+4));
			break;
   } 

	return;

  //thread_exit ();
}

void sys_halt(void){
	shutdown_power_off();
}

void sys_exit (int status){
	printf("%s: exit(%d)\n", thread_name(), status);
	thread_current()->exit_status = status;
	for(int i=3; i<128; i++){
		if(thread_current()->fd[i]!=NULL)
			sys_close(i);
	}

	struct list_elem *e = list_begin(&(thread_current())->child);
	struct thread*t;

	while(e!=list_end(&(thread_current()->child))){
		t=list_entry(e, struct thread, child_elem);
		process_wait(t->tid);

		e=list_next(e);
	}

	file_close(thread_current()->cur_file);
	thread_exit();
}

pid_t sys_exec (const char *file){
	if(file==NULL)
		return -1;
	return process_execute(file);
}

int sys_wait (pid_t pid){
	return process_wait(pid);
}

int sys_read (int fd, void *buffer, unsigned length){
	int i;
	user_vaddr(buffer);
	lock_acquire(&file_lock);
	if(fd==0){
		for(i=0; i<(int)length; i++){
			uint8_t c = input_getc();
			if(c=='\0')
				break;
		}
		lock_release(&file_lock);
		return i;
	}
	else if(fd>=3){
		if(thread_current()->fd[fd]==NULL){
			lock_release(&file_lock);
			sys_exit(-1);
		}
		int result;
		result = file_read(thread_current()->fd[fd], buffer, length);
		lock_release(&file_lock);
		return result;
	}
	else{
		lock_release(&file_lock);
		return -1;
	}
}

int sys_write (int fd, const void *buffer, unsigned length){
	user_vaddr(buffer);
	lock_acquire(&file_lock);
	if(fd==1){
		putbuf((char*)buffer, (size_t)length);
		lock_release(&file_lock);
		return length;
	}
	else if(fd>=3){
		if(thread_current()->fd[fd]==NULL){
			lock_release(&file_lock);
			sys_exit(-1);
		}
		//if(thread_current()->fd[fd]->deny_write){
		//	file_deny_write(thread_current()->fd[fd]);
		//}
		int result;
		result = file_write(thread_current()->fd[fd], buffer, length);
		lock_release(&file_lock);
		return result;
	}
	else {
		lock_release(&file_lock);
		return -1;
	}
}

int sys_fibonacci (int n){
	int a=1;
	int b=1;
	int temp;
	if(n==1)
		return 1;
	else if(n==2)
		return 1;
	else{
		for(int i=2; i<n; i++){
			temp = a+b;
			a=b;
			b=temp;
		}
		return b;
	}
}

int sys_max_of_four_int(int a, int b, int c, int d){
	int max;
	if(a>=b)
		max=a;
	else max=b;
	if(max<c)
		max=c;
	if(max<d)
		max=d;
	return max;
}

bool sys_create (const char* file, unsigned initial_size){
	if(file==NULL)
		sys_exit(-1);
	return filesys_create(file, initial_size);
}

bool sys_remove(const char* file){
	if(file==NULL)
		sys_exit(-1);
	return filesys_remove(file);
}

int sys_open(const char*file){
	if(file==NULL)
		sys_exit(-1);
	lock_acquire(&file_lock);
	struct file*fp = filesys_open(file);
	if(fp==NULL){
		lock_release(&file_lock);
		return -1;;
	}
	else{
		for(int i = 3; i<128; i++){
			if(thread_current()->fd[i]==NULL){
				//if(strcmp(thread_name(), file)==0){
				//	file_deny_write(fp);
				//}
					thread_current()->fd[i]=fp;
					lock_release(&file_lock);
					return i;
			}
		}
	}
	lock_release(&file_lock);
	return -1;
}

int sys_filesize(int fd){
	if(thread_current()->fd[fd]==NULL)
		sys_exit(-1);
	return file_length(thread_current()->fd[fd]);
}

void sys_seek(int fd, unsigned position){
	if(thread_current()->fd[fd]==NULL)
		sys_exit(-1);
	file_seek(thread_current()->fd[fd], position);
}

unsigned sys_tell(int fd){
	if(thread_current()->fd[fd]==NULL)
		sys_exit(-1);
	return file_tell(thread_current()->fd[fd]);
}

void sys_close(int fd){	
	if(thread_current()->fd[fd]==NULL)
		sys_exit(-1);

	//struct file*fp = thread_current()->fd[fd];
	file_close(thread_current()->fd[fd]);
	thread_current()->fd[fd]=NULL;
}
