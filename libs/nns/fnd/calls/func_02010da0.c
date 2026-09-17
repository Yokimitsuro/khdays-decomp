typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000




typedef enum {
    OS_ARENA_MAIN            = 0,
    OS_ARENA_MAIN_SUBPRIV    = 1,
    OS_ARENA_MAINEX          = 2,
    OS_ARENA_ITCM            = 3,
    OS_ARENA_DTCM            = 4,
    OS_ARENA_SHARED          = 5,
    OS_ARENA_WRAM_MAIN       = 6,
    OS_ARENA_WRAM_SUB        = 7,
    OS_ARENA_WRAM_SUBPRIV    = 8,
    OS_ARENA_MAX             = 9
} OSArenaId;
typedef int OSHeapHandle;
extern void * OS_AllocFromHeap(OSArenaId id, OSHeapHandle heap, u32 size);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
typedef void * (*MIAllocatorAllocFunction)(void * userdata, u32 length, u32 alignment);
typedef void (*MIAllocatorFreeFunction)(void * userdata, void * buffer);
typedef struct {
    void * prevObject;
    void * nextObject;
} NNSFndLink;
typedef struct {
    void * headObject;
    void * tailObject;
    u16 numObjects;
    u16 offset;
} NNSFndList;
typedef struct NNSiFndHeapHead NNSiFndHeapHead;
struct NNSiFndHeapHead {
    u32 signature;
    NNSFndLink link;
    NNSFndList childList;
    void * heapStart;
    void * heapEnd;
    u32 attribute;
};
typedef NNSiFndHeapHead * NNSFndHeapHandle;
typedef void (*NNSFndHeapVisitor)(void * memBlock, NNSFndHeapHandle heap, u32 userParam);
typedef struct NNSFndAllocator NNSFndAllocator;
typedef void * (*NNSFndFuncAllocatorAlloc)(NNSFndAllocator * pAllocator, u32 size);
typedef void (*NNSFndFuncAllocatorFree)(NNSFndAllocator * pAllocator, void * memBlock);
typedef struct NNSFndAllocatorFunc NNSFndAllocatorFunc;
struct NNSFndAllocatorFunc {
    NNSFndFuncAllocatorAlloc pfAlloc;
    NNSFndFuncAllocatorFree pfFree;
};
struct NNSFndAllocator {
    NNSFndAllocatorFunc const * pFunc;
    void * pHeap;
    u32 heapParam1;
    u32 heapParam2;
};

/* func_02010da0 -- NitroSystem allocator.c: AllocatorAllocForSDKHeap. */
void * func_02010da0 (NNSFndAllocator * pAllocator, u32 size)
{
    OSHeapHandle const heap = (int)pAllocator->pHeap;
    OSArenaId const id = (OSArenaId)pAllocator->heapParam1;
    return OS_AllocFromHeap(id, heap, size);
}
