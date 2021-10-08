#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

// 얘네는 syscall.c만 넣어도 상관없으려나?
// syscall.h는 두개인데 여기 넣는거 맞나?
void syscall_init (void);
void check_address(void *uaddr);
void get_argument(void *esp, int *arg, int count);

#endif /* userprog/syscall.h */
