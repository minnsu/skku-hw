#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "x86.h"
#include "proc.h"
#include "spinlock.h"

extern struct mmap_area mmt[64]; /* mmap table */

struct {
  struct spinlock lock;
  struct proc proc[NPROC];
} ptable;

#define VRUNLIMIT 0x7FFFFFFF
uint rnable_weight = 0; /* runnable weight */
// real 1 tick = 10ms, but for avoid floating operaion, 1000 unit = 1tick
const int sched_latency = 10000; /* 10tick, 1tick = 1000 unit */
const int weight_by_nice[40] = {
  /*  0 */ 88761, 71755, 56483, 46273, 36291,
  /*  5 */ 29154, 23254, 18705, 14949, 11916,
  /* 10 */  9548,  7620,  6100,  4904,  3906,
  /* 15 */  3121,  2501,  1991,  1586,  1277,
  /* 20 */  1024,   820,   655,   526,   423,
  /* 25 */   335,   272,   215,   172,   137,
  /* 30 */   110,    87,    70,    56,    45,
  /* 35 */    36,    29,    23,    18,    15
};

void update_time(struct proc *p){
  p->vruntime += p->tmptime * 1024 / p->weight;
  if(p->vruntime >= VRUNLIMIT){
    /* overflow processing */
    p->overflow_count++;
    p->vruntime -= VRUNLIMIT;
  }
  p->runtime += p->tmptime;
  p->tmptime = 0;
}

void add_rnable(int weight){
  rnable_weight += weight;
}
void rmv_rnable(struct proc *p){
  rnable_weight -= p->weight;
  update_time(p);
}

static struct proc *initproc;

int nextpid = 1;
extern void forkret(void);
extern void trapret(void);

static void wakeup1(void *chan);

void
pinit(void)
{
  initlock(&ptable.lock, "ptable");
}

// Must be called with interrupts disabled
int
cpuid() {
  return mycpu()-cpus;
}

// Must be called with interrupts disabled to avoid the caller being
// rescheduled between reading lapicid and running through the loop.
struct cpu*
mycpu(void)
{
  int apicid, i;
  
  if(readeflags()&FL_IF)
    panic("mycpu called with interrupts enabled\n");
  
  apicid = lapicid();
  // APIC IDs are not guaranteed to be contiguous. Maybe we should have
  // a reverse map, or reserve a register to store &cpus[i].
  for (i = 0; i < ncpu; ++i) {
    if (cpus[i].apicid == apicid)
      return &cpus[i];
  }
  panic("unknown apicid\n");
}

// Disable interrupts so that we are not rescheduled
// while reading proc from the cpu structure
struct proc*
myproc(void) {
  struct cpu *c;
  struct proc *p;
  pushcli();
  c = mycpu();
  p = c->proc;
  popcli();
  return p;
}

//PAGEBREAK: 32
// Look in the process table for an UNUSED proc.
// If found, change state to EMBRYO and initialize
// state required to run in the kernel.
// Otherwise return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  char *sp;

  acquire(&ptable.lock);

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == UNUSED)
      goto found;

  release(&ptable.lock);
  return 0;

found:
  p->nice = 20; /* default priority: 20 */
  p->weight = 1024;
  p->timeslice = 0;
  p->vruntime = 0;
  p->runtime = 0;
  p->tmptime = 0;
  p->overflow_count = 0;

  p->state = EMBRYO;
  p->pid = nextpid++;

  release(&ptable.lock);

  // Allocate kernel stack.
  if((p->kstack = kalloc()) == 0){
    p->state = UNUSED;
    return 0;
  }
  sp = p->kstack + KSTACKSIZE;

  // Leave room for trap frame.
  sp -= sizeof *p->tf;
  p->tf = (struct trapframe*)sp;

  // Set up new context to start executing at forkret,
  // which returns to trapret.
  sp -= 4;
  *(uint*)sp = (uint)trapret;

  sp -= sizeof *p->context;
  p->context = (struct context*)sp;
  memset(p->context, 0, sizeof *p->context);
  p->context->eip = (uint)forkret;

  return p;
}

//PAGEBREAK: 32
// Set up first user process.
void
userinit(void)
{
  struct proc *p;
  extern char _binary_initcode_start[], _binary_initcode_size[];

  p = allocproc();
  
  initproc = p;
  if((p->pgdir = setupkvm()) == 0)
    panic("userinit: out of memory?");
  inituvm(p->pgdir, _binary_initcode_start, (int)_binary_initcode_size);
  p->sz = PGSIZE;
  memset(p->tf, 0, sizeof(*p->tf));
  p->tf->cs = (SEG_UCODE << 3) | DPL_USER;
  p->tf->ds = (SEG_UDATA << 3) | DPL_USER;
  p->tf->es = p->tf->ds;
  p->tf->ss = p->tf->ds;
  p->tf->eflags = FL_IF;
  p->tf->esp = PGSIZE;
  p->tf->eip = 0;  // beginning of initcode.S

  safestrcpy(p->name, "initcode", sizeof(p->name));
  p->cwd = namei("/");

  // this assignment to p->state lets other cores
  // run this process. the acquire forces the above
  // writes to be visible, and the lock is also needed
  // because the assignment might not be atomic.
  acquire(&ptable.lock);

  p->state = RUNNABLE;
  add_rnable(p->weight);

  release(&ptable.lock);
}

// Grow current process's memory by n bytes.
// Return 0 on success, -1 on failure.
int
growproc(int n)
{
  uint sz;
  struct proc *curproc = myproc();

  sz = curproc->sz;
  if(n > 0){
    if((sz = allocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  } else if(n < 0){
    if((sz = deallocuvm(curproc->pgdir, sz, sz + n)) == 0)
      return -1;
  }
  curproc->sz = sz;
  switchuvm(curproc);
  return 0;
}

// Create a new process copying p as the parent.
// Sets up stack to return as if from system call.
// Caller must set state of returned proc to RUNNABLE.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *curproc = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy process state from proc.
  if((np->pgdir = copyuvm(curproc->pgdir, curproc->sz)) == 0){
    kfree(np->kstack);
    np->kstack = 0;
    np->state = UNUSED;
    return -1;
  }
  np->sz = curproc->sz;
  np->parent = curproc;
  *np->tf = *curproc->tf;

  // Clear %eax so that fork returns 0 in the child.
  np->tf->eax = 0;

  for(i = 0; i < NOFILE; i++)
    if(curproc->ofile[i])
      np->ofile[i] = filedup(curproc->ofile[i]);
  np->cwd = idup(curproc->cwd);

  uint empty = 0, j;
  char *mem;
  for(i = 0; i < 64; i++){
    if(mmt[i].p == curproc){
      for(; empty < 64; empty++){
        if(mmt[empty].flags == 0)
          break;
      }
      if(mmt[i].f)
        filedup(mmt[i].f);
      mmt[empty].f = mmt[i].f;
      mmt[empty].addr = mmt[i].addr;
      mmt[empty].length = mmt[i].length;
      mmt[empty].offset = mmt[i].offset;
      mmt[empty].prot = mmt[i].prot;
      mmt[empty].flags = mmt[i].flags;
      mmt[empty].p = np;
      mmt[empty].noalloc_count = mmt[i].noalloc_count;
      
      pte_t *pte;
      if(mmt[i].noalloc_count != mmt[i].length / PGSIZE){
        for(j = 0; j < mmt[i].length; j += PGSIZE){
          pte = walkpgdir(curproc->pgdir, (char *)(mmt[i].addr + j), 0);
          if(!(*pte & PTE_P) || pte == 0) /* parent process have not real mapping in addr + j */
            continue;
          if((mem = kalloc()) == 0)
            return -1;
          memmove((void *)mem, (const void *)mmt[i].addr + j, PGSIZE); /* child has same content of memory */

          if(mappages(np->pgdir, (void *)(mmt[i].addr + j), PGSIZE, V2P(mem), mmt[i].prot | PTE_U) < 0){
            kfree(mem);
            return -1;
          }
        }
      }
    }
  }

  safestrcpy(np->name, curproc->name, sizeof(curproc->name));

  pid = np->pid;

  acquire(&ptable.lock);

  np->state = RUNNABLE;
  np->overflow_count = curproc->overflow_count;
  np->vruntime = curproc->vruntime;
  np->nice = curproc->nice;
  add_rnable(np->weight);

  release(&ptable.lock);

   return pid;
}

// Exit the current process.  Does not return.
// An exited process remains in the zombie state
// until its parent calls wait() to find out it exited.
void
exit(void)
{
  struct proc *curproc = myproc();
  struct proc *p;
  int fd;

  if(curproc == initproc)
    panic("init exiting");

  // Close all open files.
  for(fd = 0; fd < NOFILE; fd++){
    if(curproc->ofile[fd]){
      fileclose(curproc->ofile[fd]);
      curproc->ofile[fd] = 0;
    }
  }

  // Unmap mapped address.
  int i;
  for(i = 0; i < 64; i++){
    if(mmt[i].p == curproc){
      if(mmt[i].f)
        fileclose(mmt[i].f);
      memset((void *)&mmt[i], 0, sizeof(struct mmap_area));
    }
  }

  begin_op();
  iput(curproc->cwd);
  end_op();
  curproc->cwd = 0;

  acquire(&ptable.lock);

  // Parent might be sleeping in wait().
  wakeup1(curproc->parent);

  // Pass abandoned children to init.
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->parent == curproc){
      p->parent = initproc;
      if(p->state == ZOMBIE)
        wakeup1(initproc);
    }
  }

  // Jump into the scheduler, never to return.
  curproc->state = ZOMBIE;
  rmv_rnable(curproc);
  sched();
  panic("zombie exit");
}

// Wait for a child process to exit and return its pid.
// Return -1 if this process has no children.
int
wait(void)
{
  struct proc *p;
  int havekids, pid;
  struct proc *curproc = myproc();
  
  acquire(&ptable.lock);
  for(;;){
    // Scan through table looking for exited children.
    havekids = 0;
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->parent != curproc)
        continue;
      havekids = 1;
      if(p->state == ZOMBIE){
        // Found one.
        pid = p->pid;
        kfree(p->kstack);
        p->kstack = 0;
        freevm(p->pgdir);
        p->pid = 0;
        p->parent = 0;
        p->name[0] = 0;
        p->killed = 0;
        p->state = UNUSED;
        release(&ptable.lock);
        return pid;
      }
    }

    // No point waiting if we don't have any children.
    if(!havekids || curproc->killed){
      release(&ptable.lock);
      return -1;
    }

    // Wait for children to exit.  (See wakeup1 call in proc_exit.)
    sleep(curproc, &ptable.lock);  //DOC: wait-sleep
  }
}

//PAGEBREAK: 42
// Per-CPU process scheduler.
// Each CPU calls scheduler() after setting itself up.
// Scheduler never returns.  It loops, doing:
//  - choose a process to run
//  - swtch to start running that process
//  - eventually that process transfers control
//      via swtch back to the scheduler.
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  c->proc = 0;
  
  struct proc *select;
  for(;;){
    // Enable interrupts on this processor.
    sti();

    // Loop over process table looking for process to run.
    acquire(&ptable.lock);
    for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
      if(p->state != RUNNABLE)
        continue;

      select = p;
      for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
        if(p->state != RUNNABLE)
          continue;
        if(p->overflow_count == select->overflow_count){
          if(p->vruntime < select->vruntime)
            select = p;
        } else if(p->overflow_count < select->overflow_count){
          select = p;
        }
      }
      p = select;
      p->timeslice = sched_latency * p->weight / rnable_weight;
      
      // Switch to chosen process.  It is the process's job
      // to release ptable.lock and then reacquire it
      // before jumping back to us.
      c->proc = p;
      switchuvm(p);
      p->state = RUNNING;

      swtch(&(c->scheduler), p->context);
      switchkvm();

      // Process is done running for now.
      // It should have changed its p->state before coming back.
      c->proc = 0;
    }
    release(&ptable.lock);

  }
}

// Enter scheduler.  Must hold only ptable.lock
// and have changed proc->state. Saves and restores
// intena because intena is a property of this
// kernel thread, not this CPU. It should
// be proc->intena and proc->ncli, but that would
// break in the few places where a lock is held but
// there's no process.
void
sched(void)
{
  int intena;
  struct proc *p = myproc();

  if(!holding(&ptable.lock))
    panic("sched ptable.lock");
  if(mycpu()->ncli != 1)
    panic("sched locks");
  if(p->state == RUNNING)
    panic("sched running");
  if(readeflags()&FL_IF)
    panic("sched interruptible");
  intena = mycpu()->intena;
  swtch(&p->context, mycpu()->scheduler);
  mycpu()->intena = intena;
}

// Give up the CPU for one scheduling round.
void
yield(void)
{
  acquire(&ptable.lock);  //DOC: yieldlock
  myproc()->state = RUNNABLE;
  update_time(myproc());
  sched();
  release(&ptable.lock);
}

// A fork child's very first scheduling by scheduler()
// will swtch here.  "Return" to user space.
void
forkret(void)
{
  static int first = 1;
  // Still holding ptable.lock from scheduler.
  release(&ptable.lock);

  if (first) {
    // Some initialization functions must be run in the context
    // of a regular process (e.g., they call sleep), and thus cannot
    // be run from main().
    first = 0;
    iinit(ROOTDEV);
    initlog(ROOTDEV);
  }

  // Return to "caller", actually trapret (see allocproc).
}

// Atomically release lock and sleep on chan.
// Reacquires lock when awakened.
void
sleep(void *chan, struct spinlock *lk)
{
  struct proc *p = myproc();
  
  if(p == 0)
    panic("sleep");

  if(lk == 0)
    panic("sleep without lk");

  // Must acquire ptable.lock in order to
  // change p->state and then call sched.
  // Once we hold ptable.lock, we can be
  // guaranteed that we won't miss any wakeup
  // (wakeup runs with ptable.lock locked),
  // so it's okay to release lk.
  if(lk != &ptable.lock){  //DOC: sleeplock0
    acquire(&ptable.lock);  //DOC: sleeplock1
    release(lk);
  }
  // Go to sleep.
  p->chan = chan;
  p->state = SLEEPING;
  rmv_rnable(p);

  sched();

  // Tidy up.
  p->chan = 0;

  // Reacquire original lock.
  if(lk != &ptable.lock){  //DOC: sleeplock2
    release(&ptable.lock);
    acquire(lk);
  }
}

//PAGEBREAK!
// Wake up all processes sleeping on chan.
// The ptable lock must be held.
static void
wakeup1(void *chan)
{
  struct proc *p;
  int min_vrun = VRUNLIMIT;
  int min_overc = VRUNLIMIT;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state != RUNNABLE)
      continue;
    if(p->overflow_count == min_overc){
      if(p->vruntime < min_vrun){
        min_vrun = p->vruntime;
      }
    } else if(p->overflow_count < min_overc){
      min_overc = p->overflow_count;
      min_vrun = p->vruntime;
    }
  }
  int tick_v;
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++)
    if(p->state == SLEEPING && p->chan == chan){
      p->state = RUNNABLE;

      p->overflow_count = min_overc < VRUNLIMIT ? min_overc : 0;
      tick_v = 1000 * 1024 / p->weight;
      p->vruntime = min_vrun < VRUNLIMIT ? min_vrun - tick_v : 0;
      if(0 > min_vrun - tick_v){ /* underflow */
        if(p->overflow_count > 0){
          p->overflow_count--;
          p->vruntime = VRUNLIMIT - (tick_v - min_vrun);
        } else {
          p->vruntime = 0;
        }
      }
      add_rnable(p->weight);
    }
}

// Wake up all processes sleeping on chan.
void
wakeup(void *chan)
{
  acquire(&ptable.lock);
  wakeup1(chan);
  release(&ptable.lock);
}

// Kill the process with the given pid.
// Process won't exit until it returns
// to user space (see trap in trap.c).
int
kill(int pid)
{
  struct proc *p;
  struct proc *tmp;

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      p->killed = 1;
      // Wake process from sleep if necessary.
      if(p->state == SLEEPING){
        int min_vrun = VRUNLIMIT;
        int min_overc = VRUNLIMIT;
        int tick_v;
        tmp = p;
        for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
          if(p->state != RUNNABLE)
            continue;
          if(p->overflow_count == min_overc){
            if(p->vruntime < min_vrun){
              min_vrun = p->vruntime;
            }
          } else if(p->overflow_count < min_overc){
            min_overc = p->overflow_count;
            min_vrun = p->vruntime;
          }
        }
        p = tmp;
        p->overflow_count = min_overc < VRUNLIMIT ? min_overc : 0;
        tick_v = 1000 * 1024 / p->weight;
        p->vruntime = min_vrun < VRUNLIMIT ? min_vrun - tick_v : 0;
        if(0 > min_vrun - tick_v){ /* underflow */
          if(p->overflow_count > 0){
            p->overflow_count--;
            p->vruntime = VRUNLIMIT - (tick_v - min_vrun);
          } else {
            p->vruntime = 0;
          }
        }
        p->state = RUNNABLE;
        add_rnable(p->weight);
      }
      release(&ptable.lock);
      return 0;
    }
  }
  release(&ptable.lock);
  return -1;
}

//PAGEBREAK: 36
// Print a process listing to console.  For debugging.
// Runs when user types ^P on console.
// No lock to avoid wedging a stuck machine further.
void
procdump(void)
{
  static char *states[] = {
  [UNUSED]    "unused",
  [EMBRYO]    "embryo",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  int i;
  struct proc *p;
  char *state;
  uint pc[10];

  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->state == UNUSED)
      continue;
    if(p->state >= 0 && p->state < NELEM(states) && states[p->state])
      state = states[p->state];
    else
      state = "???";
    cprintf("%d %s %s", p->pid, state, p->name);
    if(p->state == SLEEPING){
      getcallerpcs((uint*)p->context->ebp+2, pc);
      for(i=0; i<10 && pc[i] != 0; i++)
        cprintf(" %p", pc[i]);
    }
    cprintf("\n");
  }
}

/* -------------------- */
int
getnice(int pid)
{
  struct proc *p;
  int ret = -1;
  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      ret = p->nice;
      break;
    }
  }
  release(&ptable.lock);
  return ret;
}

int
setnice(int pid, int value)
{
  struct proc *p;
  int ret = -1;
  if(value < 0 || value > 39){
    goto end;
  }
  uint before_weight;
  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(p->pid == pid){
      before_weight = p->weight;
      p->nice = value;
      p->weight = weight_by_nice[p->nice];
      if(p->state == RUNNABLE || p->state == RUNNING){
        rnable_weight -= before_weight;
        rnable_weight += p->weight;
        /* new nice value -> new vruntime? or not? */
      }
      ret = 0;
      break;
    }
  }
  release(&ptable.lock);

  end:
  return ret;
}

void align(char *new, int c, int flag, char *str, int num){
  int i, j;
  int counter = 1;
  switch(flag){
    case 0: /* string */
      for(i = 0; str[i] != '\0'; i++)
        new[i] = str[i];
      for(; i < c; i++)
        new[i] = ' ';
      new[i] = '\0';
      break;
    case 1: /* integer */
      for(i = 10; num / i != 0; i *= 10)
        counter++;
      i /= 10;
      for(j = 0; j < counter; j++){
        new[j] = '0' + num / i;
        num %= i;
        i /= 10;
      }
      for(; j < c; j++)
        new[j] = ' ';
      new[j] = '\0';
      break;
  }
}

void overflow_print(struct proc *p){
  char vruntime[16] = "000000000000000";
  int key = 1000000000;
  int tmpVrun = p->vruntime;
  int i;
  for(i = 5; i < 16 && tmpVrun; i++){
    vruntime[i] = '0' + tmpVrun / key;
    tmpVrun %= key;
    key /= 10;
  }
  char overflow[16] = "000002147483647";
  
  char result[16] = "000000000000000";
  int sum = 0;
  int carry = 0;
  for(i = 0; i < p->overflow_count; i++){
    for(int j = 14; j >= 0; j--){
      sum = overflow[j] - '0' + result[j] - '0' + carry;
      carry = sum / 10;
      sum %= 10;
      result[j] = sum + '0';
    }
  }
  sum = 0;
  carry = 0;
  for(i = 14; i >= 0; i--){
    sum = vruntime[i] - '0' + result[i] - '0' + carry;
    carry = sum / 10;
    sum %= 10;
    result[i] = sum + '0';
  }

  result[15] = '\0';
  char *start = result;
  while(start[0] == '0'){
    start++;
  }
  cprintf("%s\n", (start[0] == '\0' ? "0" : start));
}

void printall(struct proc *p){
  char *states[] = {"UNUSED", "EMBRYO", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE"};
  char tmp_str[16];

  align(tmp_str, 11, 0, p->name, -1);
  cprintf("%s", tmp_str);
  align(tmp_str, 10, 1, "no use", p->pid);
  cprintf("%s", tmp_str);
  align(tmp_str, 10, 0, states[p->state], -1);
  cprintf("%s", tmp_str);
  align(tmp_str, 13, 1, "no use", p->nice);
  cprintf("%s", tmp_str);
  align(tmp_str, 19, 1, "no use", p->runtime / p->weight);
  cprintf("%s", tmp_str);
  align(tmp_str, 15, 1, "no use", p->runtime);
  cprintf("%s", tmp_str);
  overflow_print(p);
  // cprintf("%d\n", p->vruntime);
}

void
ps(int pid)
{
  struct proc *p;
  if(pid == 0)
    cprintf("name       pid       state     priority     runtime/weight     runtime        vruntime       tick %d\n", ticks * 1000);

  acquire(&ptable.lock);
  for(p = ptable.proc; p < &ptable.proc[NPROC]; p++){
    if(!p->state) /* ignore UNUSED process */
      continue;
    if(!pid){
      printall(p);
    } else if(p->pid == pid){ /* or (pid && p->pid == pid)*/
      cprintf("name       pid       state     priority     runtime/weight     runtime        vruntime       tick %d\n", ticks * 1000);
      printall(p);
      break;
    }
  }
  release(&ptable.lock);
}