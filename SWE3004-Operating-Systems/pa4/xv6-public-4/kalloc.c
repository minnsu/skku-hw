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

struct page pages[PHYSTOP/PGSIZE];
struct page *page_lru_head;
int num_free_pages = PHYSTOP/PGSIZE;
int num_lru_pages;

struct spinlock page_lock;
struct page *page_lru_tail;
extern const int max_blkno;
extern const int max_bitmap_idx;

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
  memset((void *)swap_sp.bitmap, 0, max_bitmap_idx + 1); // SWAPMAX(99500) / (PGSIZE / BSIZE) / 8;
  swap_sp.bitmap[max_bitmap_idx] |= 0x7; // Mark bitmap end point
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
  if(kmem.use_lock)
    release(&kmem.lock);
}

// Swap out pages
int
reclaim() {
  if(num_lru_pages == 0)
    return 0;
  // swapwrite call sleeplock(ide) -> cpu can have atmost one lock -> should be release kmem.lock
  release(&kmem.lock);
  acquire(&page_lock);
  pte_t *pte;
  struct page *victim;
  for(victim = page_lru_tail; /* Always escapable */ ; victim = victim->prev) {
    pte = walkpgdir(victim->pgdir, victim->vaddr, 0);
    if(*pte & PTE_A) {
      *pte &= ~PTE_A;
      // Circular list and victim target is always head -> Move position of head, tail by one
      page_lru_tail = victim->prev;
      page_lru_head = victim;
    } else if(!(*pte & PTE_U))
      lru_delete(P2V(PTE_ADDR(*pte)));
    else
      break;
  }
  release(&page_lock);

  int blkno = get_blkno();
  if(blkno < 0) // no more swap space
    return 0;
  swapwrite(victim->vaddr, blkno);

  char *addr = P2V(PTE_ADDR(*pte));
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
  if(!r) {
    if(reclaim())
      goto try_again;
    else {
      cprintf("kalloc: Out of memory\n");
    }
  }
  if(r)
    kmem.freelist = r->next;
  if(kmem.use_lock)
    release(&kmem.lock);
  return (char*)r;
}

