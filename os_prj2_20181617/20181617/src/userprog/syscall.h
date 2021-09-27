#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include "process.h"

typedef int pid_t;
#define PID_ERROR ((pid_t)-1)

void user_vaddr(const void * vaddr);
void syscall_init (void);
void sys_halt(void);
void sys_exit(int status);
pid_t sys_exec(const char*file);
int sys_wait(pid_t);
int sys_read(int fd, void *buffer, unsigned length);
int sys_write(int fd, const void *buffer, unsigned length);
int sys_fibonacci(int n);
int sys_max_of_four_int(int a, int b, int c, int d);
bool sys_create(const char*file, unsigned initial_size);
bool sys_remove(const char* file);
int sys_open(const char* file);
int sys_filesize(int fd);
void sys_seek(int fd, unsigned position);
unsigned sys_tell(int fd);
void sys_close(int fd);


#endif /* userprog/syscall.h */
