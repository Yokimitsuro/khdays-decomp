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
typedef struct NNSiFndExpHeapMBlockHead NNSiFndExpHeapMBlockHead;
struct NNSiFndExpHeapMBlockHead {
    u16 signature;
    u16 attribute;
    u32 blockSize;
    NNSiFndExpHeapMBlockHead * pMBHeadPrev;
    NNSiFndExpHeapMBlockHead * pMBHeadNext;
};
typedef struct NNSiFndExpMBlockList NNSiFndExpMBlockList;
struct NNSiFndExpMBlockList {
    NNSiFndExpHeapMBlockHead * head;
    NNSiFndExpHeapMBlockHead * tail;
};
typedef struct NNSiFndExpHeapHead NNSiFndExpHeapHead;
struct NNSiFndExpHeapHead {
    NNSiFndExpMBlockList mbFreeList;
    NNSiFndExpMBlockList mbUsedList;
    u16 groupID;
    u16 feature;
};
typedef void (*NNSFndHeapVisitor)(void * memBlock, NNSFndHeapHandle heap, u32 userParam);
typedef u32 NNSiUIntPtr;
inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr)
{
    return (NNSiUIntPtr)ptr;
}
inline void* AddU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}
inline void* SubU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) - val );
}
typedef struct NNSiMemRegion NNSiMemRegion;
struct NNSiMemRegion {
    void * start;
    void * end;
};
static inline NNSiFndExpHeapHead * GetExpHeapHeadPtrFromHeapHead (NNSiFndHeapHead * pHHead)
{
    return AddU32ToPtr(pHHead, sizeof(NNSiFndHeapHead));
}
static inline NNSiFndExpHeapHead * GetExpHeapHeadPtrFromHandle (NNSFndHeapHandle heap)
{
    return GetExpHeapHeadPtrFromHeapHead(heap);
}
static inline NNSiFndExpHeapMBlockHead * GetMBlockHeadPtr (void * memBlock)
{
    return SubU32ToPtr(memBlock, sizeof(NNSiFndExpHeapMBlockHead));
}
extern void GetRegionOfMBlock (NNSiMemRegion * region, NNSiFndExpHeapMBlockHead * block);
extern NNSiFndExpHeapMBlockHead * RemoveMBlock (NNSiFndExpMBlockList * list, NNSiFndExpHeapMBlockHead * block);
extern BOOL RecycleRegion (NNSiFndExpHeapHead * pEHHead, const NNSiMemRegion * pRegion);

/* func_0201098c -- NitroSystem expheap.c: NNS_FndFreeToExpHeap. */
void func_0201098c (NNSFndHeapHandle heap, void * memBlock)
{

    {
        NNSiFndHeapHead * pHeapHd = heap;
        NNSiFndExpHeapHead * pExpHeapHd = GetExpHeapHeadPtrFromHandle(pHeapHd);
        NNSiFndExpHeapMBlockHead * pMBHead = GetMBlockHeadPtr(memBlock);
        NNSiMemRegion region;


        GetRegionOfMBlock(&region, pMBHead);
        (void)RemoveMBlock(&pExpHeapHd->mbUsedList, pMBHead);
        (void)RecycleRegion(pExpHeapHd, &region);
    }
}
