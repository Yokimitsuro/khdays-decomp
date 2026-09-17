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

#define NNS_FND_INIT_LIST(list, structName, linkName) NNS_FndInitList(list, offsetof(structName, linkName))

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
void NNS_FndInitList(NNSFndList * list, u16 offset);
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
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndHeap;
typedef struct NNSSndHeap {
    NNSFndHeapHandle handle;
    NNSFndList sectionList;
} NNSSndHeap;
typedef struct NNSSndHeapSection {
    NNSFndList blockList;
    NNSFndLink link;
} NNSSndHeapSection;
extern BOOL func_0201bb6c(NNSSndHeap * heap);
extern BOOL func_0201bb6c (NNSSndHeap * heap);

/* func_0201bb38 -- NitroSDK heap.c: InitHeap. */
BOOL func_0201bb38 (NNSSndHeap * heap, NNSFndHeapHandle handle)
{
    NNS_FND_INIT_LIST(&heap->sectionList, NNSSndHeapSection, link);
    heap->handle = handle;

    if (!func_0201bb6c(heap)) {
        return FALSE;
    }

    return TRUE;
}
