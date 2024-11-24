// Physical memory allocator, intended to allocate
// memory for user processes, kernel stacks, page table pages,
// and pipe buffers. Allocates 4096-byte pages.

#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "spinlock.h"
#include "proc.h"

void freerange(void *vstart, void *vend);
extern char end[]; // first address after kernel loaded from ELF file
                   // defined by the kernel linker script in kernel.ld

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  int use_lock;
  struct run *freelist;
} kmem;

struct spinlock page_lock;
struct page pages[PHYSTOP/PGSIZE];
struct page *page_lru_head;
struct page *page_lru_tail; // lru에서 뒤에 추가?
int num_free_pages;
int num_lru_pages;

// Initialization happens in two phases.
// 1. main() calls kinit1() while still using entrypgdir to place just
// the pages mapped by entrypgdir on free list.
// 2. main() calls kinit2() with the rest of the physical pages
// after installing a full page table that maps them on all cores.
void
kinit1(void *vstart, void *vend)
{
  initlock(&kmem.lock, "kmem");
  kmem.use_lock = 0;
  freerange(vstart, vend);
}

struct {
  struct spinlock lock;
  char *bitmap;
} swap_sp;

void
kinit2(void *vstart, void *vend)
{
  freerange(vstart, vend);
  kmem.use_lock = 1;

  // make swap space
  if((swap_sp.bitmap = kalloc()) == 0) {
    panic("cannot turn on swap space");
  }
  memset((void *)swap_sp.bitmap, 0xFF, PGSIZE);
  memset((void *)swap_sp.bitmap, 0, 1555);
  swap_sp.bitmap[1554] |= 0x7; // swap space bit map 끝 표시
}

void
freerange(void *vstart, void *vend)
{
  char *p;
  p = (char*)PGROUNDUP((uint)vstart);
  for(; p + PGSIZE <= (char*)vend; p += PGSIZE)
    kfree(p);
}
//PAGEBREAK: 21
// Free the page of physical memory pointed at by v,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(char *v)
{
  struct run *r;

  if((uint)v % PGSIZE || v < end || V2P(v) >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(v, 1, PGSIZE);

  if(kmem.use_lock)
    acquire(&kmem.lock);
  r = (struct run*)v;
  r->next = kmem.freelist;
  kmem.freelist = r;
  num_free_pages++;
  if(kmem.use_lock)
    release(&kmem.lock);
}

int
reclaim() {
  if(num_lru_pages == 0)
    return 0;
  
  release(&kmem.lock); // swapwrite에서 sleeplock(ide) -> lock 한개만 가질 수 있음 -> kmem lock 해제
  acquire(&page_lock);
  pte_t *pte;
  struct page *victim;
  for(victim = page_lru_head; /* 무조건 탈출 가능? */ ; victim = victim->next) {
    pte = walkpgdir(victim->pgdir, victim->vaddr, 0);
    if(*pte & PTE_A) {
      *pte &= ~PTE_A;
      // circular이고, victim target은 항상 head이므로 head, tail의 위치만 한 칸씩 이동
      page_lru_head = victim->next;
      page_lru_tail = victim;
    } else if(!(*pte & PTE_U))
      lru_delete(P2V(PTE_ADDR(*pte)));
    else
      break;
  }
  release(&page_lock);
  cprintf("victim's pgdir : 0x%x, vaddr : 0x%x\n", victim->pgdir, victim->vaddr);
  int blkno = get_blkno();
  swapwrite(victim->vaddr, blkno);
  
  char *addr = P2V(PTE_ADDR(*pte));
  uint idx = V2P(addr) >> 12;
  cprintf("idx : %d, pgdir : 0x%x, vaddr : 0x%x\n", idx, pages[idx].pgdir, pages[idx].vaddr);
  lru_delete(addr);
  kfree(addr);
  
  *pte &= 0xFFF;
  *pte &= ~PTE_P;
  *pte |= blkno << 12;

  return 1;
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
char*
kalloc(void)
{
  struct run *r;

try_again:
  if(kmem.use_lock)
    acquire(&kmem.lock);
  r = kmem.freelist;
 if(!r && reclaim())
	  goto try_again;
  if(r){
    kmem.freelist = r->next;
    num_free_pages--;
  }
  if(kmem.use_lock)
    release(&kmem.lock);
  return (char*)r;
}

int
freemem(){
  return num_free_pages;
}

extern int last_blkno;
extern int free_bitmap;

int
minsutest(int flag, char *va, int blkno)
{
  struct page *tmp = page_lru_head;
  int i;
  struct proc *p = myproc();
  pte_t *pte;
  char *addr;
  switch(flag){ 
  case 0: // look up lru_list;
    cprintf("\n***** [ lru list look up testing ] *****\n");
    cprintf("lru first 10 nodes => ");
    for(i = 0; tmp != page_lru_tail && i < 10; tmp = tmp->next, i++) {
      cprintf("[ pgdir : 0x%x ", tmp->pgdir);
      cprintf("vaddr : 0x%x] ", tmp->vaddr);
      if(i % 3 == 0)
        cprintf("\n");
    }

    tmp = page_lru_tail;
    cprintf("\n\nlru last 10 nodes => ");
    for(i = 0; tmp != page_lru_head && i < 10; tmp = tmp->prev, i++) {
      cprintf("[ pgdir : 0x%x ", tmp->pgdir);
      cprintf("vaddr : 0x%x] ", tmp->vaddr);
      if(i % 3 == 0)
        cprintf("\n");
    }
    cprintf("****************************************\n");
    return (int) page_lru_head->vaddr;
  case 1: // force swap out testing
    cprintf("\n****** [ force swap out testing ] ******\n");
    pte = walkpgdir(p->pgdir, va, 0);
    cprintf("*pte of va : 0x%x\n", *pte);
    addr = P2V(PTE_ADDR(*pte));
    
    swapwrite(va, blkno);

    lru_delete(addr);
    kfree(addr);

    *pte &= ~PTE_P;
    *pte &= 0xFFF;
    *pte |= blkno << 12;

    cprintf("*pte after swapout : 0x%x\n", *pte);
    cprintf("last blkno : %d\n", last_blkno);
    cprintf("****************************************\n");
    return 0;
  case 2: // force swap in testing : no needed
    cprintf("\n******** [ free bitmap count ] *********\n");
    cprintf("free_bitmap : %d\n", free_bitmap);
    cprintf("last blkno : 0x%x\n", last_blkno);
    cprintf("****************************************\n");
    return 0;
  }
  return -1;
}