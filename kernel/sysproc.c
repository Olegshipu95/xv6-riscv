#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "ps.h"

uint64
sys_exit(void) {
    int n;
    argint(0, &n);
    exit(n);
    return 0;  // not reached
}

uint64
sys_getpid(void) {
    return myproc()->pid;
}

uint64
sys_fork(void) {
    return fork();
}

uint64
sys_wait(void) {
    uint64 p;
    argaddr(0, &p);
    return wait(p);
}

uint64
sys_sbrk(void) {
    uint64 addr;
    int n;

    argint(0, &n);
    addr = myproc()->sz;
    if (growproc(n) < 0)
        return -1;
    return addr;
}

uint64
sys_sleep(void) {
    int n;
    uint ticks0;

    argint(0, &n);
    acquire(&tickslock);
    ticks0 = ticks;
    while (ticks - ticks0 < n) {
        if (killed(myproc())) {
            release(&tickslock);
            return -1;
        }
        sleep(&ticks, &tickslock);
    }
    release(&tickslock);
    return 0;
}

uint64
sys_kill(void) {
    int pid;

    argint(0, &pid);
    return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void) {
    uint xticks;

    acquire(&tickslock);
    xticks = ticks;
    release(&tickslock);
    return xticks;
}

uint64 sys_dump(void) {
    dump();
    return 0;
}

uint64 sys_dump2(void) {
    int pid;
    int register_number;
    uint64 return_value;
    argint(0, &pid);
    argint(1, &register_number);
    argaddr(2, &return_value);
    int x = dump2(pid, register_number, return_value);
    return x;
}

uint64 sys_procinfo(void) {
    int argc;
//    uint64 argv;
    int flag;
//    char *pptr;
    argint(0, &argc);
    argint(1, &flag);
//    argaddr(1, &argv);
//    argstr(1, pptr, 2);
    if (argc == 1) {
        terminal_proc_info();
        return 0;
    } else if (argc == 2) {
        if(flag == x){
            all_proc_info();
            return 0;
        }
        else if(flag == a){
            terminal_proc_info();
            return 0;
        }
        else {
            return 1;
        }
//        if(pptr[0]!='x'){
//            return 1;
//        }
//        copyin(mycpu()->proc->pagetable, pptr, argv, sizeof(uint64));
//        uint64 value;
//        memcpy(&value, pptr, sizeof(value));
//        copyin(mycpu()->proc->pagetable, pptr, value, sizeof(char));
//        printf("%c", pptr[0]);
    } else {
        return 2;
    }
    return 0;
}