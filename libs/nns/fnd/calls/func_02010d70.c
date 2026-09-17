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

#define offsetof(type, member) ((u32)&(((type *)0)->member))

#define NNS_FndGetMemBlockSizeForUnitHeap(heap) (((const NNSiFndUntHeapHead *)((const u8 *)((const void *)(heap)) + sizeof(NNSiFndHeapHead)))->mBlkSize)

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
typedef struct NNSiFndUntHeapMBlockHead NNSiFndUntHeapMBlockHead;
struct NNSiFndUntHeapMBlockHead {
    NNSiFndUntHeapMBlockHead * pMBlkHdNext;
};
typedef struct NNSiFndUntMBlockList NNSiFndUntMBlockList;
struct NNSiFndUntMBlockList {
    NNSiFndUntHeapMBlockHead * head;
};
typedef struct NNSiFndUntHeapHead NNSiFndUntHeapHead;
struct NNSiFndUntHeapHead {
    NNSiFndUntMBlockList mbFreeList;
    u32 mBlkSize;
};
void * func_02010ce4(NNSFndHeapHandle heap);
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

/* func_02010d70 -- NitroSystem allocator.c: AllocatorAllocForUnitHeap. */
void * func_02010d70 (NNSFndAllocator * pAllocator, u32 size)
{
    NNSFndHeapHandle const heap = pAllocator->pHeap;

    if (size > NNS_FndGetMemBlockSizeForUnitHeap(heap)) {
        return NULL;
    }

    return func_02010ce4(heap);
}
