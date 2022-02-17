# memory layout
- `$ dmesg | less`
````
[    0.000000] e820: BIOS-provided physical RAM map:
[    0.000000] BIOS-e820: [mem 0x0000000000000000-0x000000000009f3ff] usable
[    0.000000] BIOS-e820: [mem 0x000000000009f400-0x000000000009ffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000000dc000-0x00000000000fffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000000100000-0x00000000bfedffff] usable
[    0.000000] BIOS-e820: [mem 0x00000000bfee0000-0x00000000bfefefff] ACPI data
[    0.000000] BIOS-e820: [mem 0x00000000bfeff000-0x00000000bfefffff] ACPI NVS
[    0.000000] BIOS-e820: [mem 0x00000000bff00000-0x00000000bfffffff] usable
[    0.000000] BIOS-e820: [mem 0x00000000f0000000-0x00000000f7ffffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fec00000-0x00000000fec0ffff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fee00000-0x00000000fee00fff] reserved
[    0.000000] BIOS-e820: [mem 0x00000000fffe0000-0x00000000ffffffff] reserved
[    0.000000] BIOS-e820: [mem 0x0000000100000000-0x00000016bfffffff] usable
````

# memory architecture
````
           Kernel AP
      kmalloc(), kfree()
              |
              V
        Slab Allocator
kmem_cache_create(), kmem_cache_destroy()
              |
	          V
either SLAB, SLOB, or SLUB
              |
	          V
        Buddy System
 __get_free_pages(), free_pages()
              |
	          V
page, page, ... page
(size of page could be 4096KB or 8192KB)
````

- `$ cat /proc/buddyinfo`
````
Node 0, zone      DMA      1      3      3      0      3      2      0      0      1      1      3 
Node 0, zone    DMA32      7     14     10      8      9     11     14     12     10     10    835 
Node 0, zone   Normal     18     18     28     37     33     10     10     36     22     12    639 
````

- `$ sudo cat /proc/slabinfo`
````
slabinfo - version: 2.1
# name            <active_objs> <num_objs> <objsize> <objperslab> <pagesperslab> : tunables <limit> <batchcount> <sharedfactor> : slabdata <active_slabs> <num_slabs> <sharedavail>
kvm_async_pf           0      0    136   30    1 : tunables    0    0    0 : slabdata      0      0      0
kvm_vcpu               0      0  23424    1    8 : tunables    0    0    0 : slabdata      0      0      0
kvm_mmu_page_header      0      0    168   24    1 : tunables    0    0    0 : slabdata      0      0      0
pte_list_desc          0      0     32  128    1 : tunables    0    0    0 : slabdata      0      0      0
ext4_groupinfo_4k   3724   3724    144   28    1 : tunables    0    0    0 : slabdata    133    133      0
...
````

- `$ sudo slabtop`
````
 Active / Total Objects (% used)    : 335942 / 337845 (99.4%)
 Active / Total Slabs (% used)      : 11303 / 11303 (100.0%)
 Active / Total Caches (% used)     : 85 / 117 (72.6%)
 Active / Total Size (% used)       : 85906.51K / 86766.41K (99.0%)
 Minimum / Average / Maximum Object : 0.01K / 0.26K / 22.88K

  OBJS ACTIVE  USE OBJ SIZE  SLABS OBJ/SLAB CACHE SIZE NAME                   
 47796  47796 100%    0.19K   2276       21      9104K dentry
 42465  42293   0%    0.20K   2235       19      8940K vm_area_struct
 29340  29340 100%    0.13K    978       30      3912K kernfs_node_cache
 25344  25344 100%    0.06K    396       64      1584K pid
 18122  18122 100%    0.59K    697       26     11152K inode_cache
 14076  14076 100%    0.09K    306       46      1224K anon_vma
...
````


# slabinfo
- Tool to get reports about slabs
- https://elixir.bootlin.com/linux/latest/source/tools/vm/slabinfo.c
- `$ gcc -o slabinfo slabinfo.c`
- `$ sudo ./slabinfo`
````
...
:0008192                   185    8192            1.7M         47/7/5    4 3  13  88 *
:a-0000032                 512      32           16.3K          0/0/4  128 0   0 100 *a
:a-0000048                 340      48           16.3K          0/0/4   85 0   0  99 *a
:a-0000056                 292      56           16.3K          0/0/4   73 0   0  99 *a
:A-0000064               28324      64            1.8M      403/31/47   64 0   6  98 *A
:a-0000064                1920      64          122.8K         0/0/30   64 0   0 100 *a
:a-0000104               95511     104           10.0M      2428/0/21   39 0   0  99 *a
:a-0000256                  80     224           20.4K          0/0/5   16 0   0  87 *Aa
anon_vma                 15524      80            1.4M      304/24/43   46 0   6  87 
bdev_cache                  76     816           65.5K          0/0/4   19 2   0  94 Aa
cfq_queue                  204     240           49.1K          4/0/8   17 0   0  99 
...
````
- `$ sudo ./slabinfo -a` to show alias
````
:0008192     <- kmalloc-8192 biovec-max
:a-0000032   <- jbd2_revoke_record_s fscrypt_info
:a-0000048   <- jbd2_journal_handle fscrypt_ctx
:a-0000056   <- ext4_free_data mbcache
:a-0000064   <- ext4_io_end
:A-0000064   <- fs_cache task_delay_info pid anon_vma_chain
:a-0000064   <- i915_dependency
:a-0000104   <- ext4_prealloc_space buffer_head
:a-0000256   <- jbd2_transaction_s dquot
````

# Kernel Stack
- the size of Kernel stack is very small (<= 8KB)

# check export symbol
- `$ sudo cat /proc/kallsyms | grep hugo`
````
ffffffffc06e1000 t hugo_init	[hugo]
ffffffffc06e1030 t hugo_exit	[hugo]
ffffffffc06e3000 d __this_module	[hugo]
ffffffffc06e1030 t cleanup_module	[hugo]
ffffffffc06e1000 t init_module	[hugo]
ffffffffc06e3344 b aaa	[hugo]
ffffffffc06e3340 b bbb	[hugo]
````

# kmalloc (Kernel API)
- `void *kmalloc(size_t size, gfp_t flags);`
- `void kfree(const void *block);`
- `GFP` stands for `Get Free Page`
  - `GFP_ATOMIC` cannot sleep, use in interrupt context
  - `GFP_KERNEL` can sleep, cannot be used in interrupt context
  - `GFP_DMA`
````
#include<linux/slab.h>

void *mem_ptr;

mem_ptr = kmalloc(1024, GFP_ATOMIC);
if (mem_ptr == NULL) {
	pr_info("kmalloc() failed");
	return -1;
}

if (mem_ptr) {
	kfree(mem_ptr);
	mem_ptr = NULL;
}
````

# kmem_cache (Slab Allocator)
- `struct kmem_cache *kmem_cache_create(const char *name, size_t size, size_t align, unsigned long flags, void (*ctor)(void *, struct kmem_cache *, unsigned long));`
- `void *kmem_cache_alloc(struct kmem_cache *cachep, gfp_t flags);`
- `void kmem_cache_free(struct kmem_cache *cachep, void *disp);`
- `void kmem_cache_destroy(struct kmem_cache *cachep);`
````
#include<linux/slab.h>
struct kmem_cache *cache;
void *mem1;
void *mem2;

//create
cache = kmem_cache_create("hugo", 1024, 0, 0, NULL);
if (cache == NULL) {
	pr_info("kmem_cache_create() failed\n");
	return -1;
}

//alloc
mem1 = kmem_cache_alloc(cache, GFP_KERNEL);
if (mem1 == NULL) {
	pr_info("kmem_cache_alloc() 1 failed\n");
	return -1;
}
mem2 = kmem_cache_alloc(cache, GFP_KERNEL);
if (mem2 == NULL) {
	pr_info("kmem_cache_alloc() 2 failed\n");
	return -1;
}

/free
if (mem1) {
	kmem_cache_free(cache, mem1);
	mem1 = NULL;
}
if (mem2) {
	kmem_cache_free(cache, mem2);
	mem2 = NULL;
}

//destroy
if (cache) {
	kmem_cache_destroy(cache);
	cache = NULL;
}
````
- `$ sudo ./slabinfo -a | grep hugo`
````
:0001024     <- UNIX sgpool-32 biovec-64 UDP UDP-Lite kmalloc-1024 hugo
````
- `$ sudo ./slabinfo`
````
Name                   Objects Objsize           Space Slabs/Part/Cpu  O/S O %Fr %Ef Flg
...
:0001024                  2377    1024            2.4M      132/10/18   16 2   6  99 *
...
````
- `Objects` 2377 is increased after insmod



# Buddy System
- `unsigned long __get_free_pages(gfp_t gfp_mask, unsigned int order`
  - order=0=1 page
  - order=1=2 pages
  - order=2=4 pages
- `void free_pages(unsigned long addr, unsigned int order);`
````
void *mem;

mem = (void *)__get_free_pages(GFP_KERNEL, 0); //allocate 1 page
if (mem == NULL) {
	pr_info("__get_free_pages() failed");
	return -1;
}

((int *)mem)[0] = 0x12345678;
((int *)mem)[1] = 0x12345678;
((int *)mem)[100] = 0x12345678;
((int *)mem)[1000] = 0x12345678;

if (mem) {
	free_pages((unsigned long)mem, 0);
	mem = NULL;
}
````

# vmalloc
- directly access the buddy system
- don't suggest to use it
  - `void *vmalloc(unsigned long size);`
  - `void vfree(void *addr);`


# DMA
- Direct Memory Access
  - no need CPU to do the data transfer between the memory and the device
- DMA buffer restriction
  - DMA buffer must be contiguous
  - DMA buffer must start at page bound
  - DMA buffer cannot be swap-out
    - Kernel's memory does not swap-out
- `void *dma_alloc_coherent(struct device *dev, size_t size, dma_addr_t *dma_handle, gfp_t gfp);`
  - return a virtual address for the driver to access
  - `dma_handle` is a physical address
- `void dma_free_coherent(struct device *dev, size_t size, void *vaddr, dma_addr_t dma_handle);`
  - `vaddr` is the virtual address returned by dma_alloc_coherent()
- `void dma_cache_sync(struct device *dev, void *vaddr, size_t size, enum dma_data_direction direction);`
  - `vaddr` is the virtual address returned by dma_alloc_coherent()
````
enum dma_data_direction {
	DMA_BIDIRECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
};
````


