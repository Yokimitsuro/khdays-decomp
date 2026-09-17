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

#define NNS_FndAllocFromFrmHeap(heap, size) NNS_FndAllocFromExpHeapEx_0x02010bcc(heap, size, NNS_FND_HEAP_DEFAULT_ALIGNMENT)
#define NNS_FND_HEAP_DEFAULT_ALIGNMENT 4

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
void NNS_FndAppendListObject(NNSFndList * list, void * object);
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
void * NNS_FndAllocFromExpHeapEx_0x02010bcc(NNSFndHeapHandle heap, u32 size, int alignment);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndHeap;
typedef void (*NNSSndHeapDisposeCallback)(void * mem, u32 size, u32 data1, u32 data2);
typedef struct NNSSndHeap {
    NNSFndHeapHandle handle;
    NNSFndList sectionList;
} NNSSndHeap;
typedef struct NNSSndHeapSection {
    NNSFndList blockList;
    NNSFndLink link;
} NNSSndHeapSection;
extern void NNS_FndInitListWithOffset0(NNSSndHeapSection * section);
extern void NNS_FndInitListWithOffset0 (NNSSndHeapSection * section);

/* func_0201bb6c -- NitroSystem heap.c: NewSection. */
BOOL func_0201bb6c (NNSSndHeap * heap)
{
    NNSSndHeapSection * section;

    section = (NNSSndHeapSection *)NNS_FndAllocFromFrmHeap(heap->handle, sizeof(NNSSndHeapSection));
    if (section == NULL) {
        return FALSE;
    }
    NNS_FndInitListWithOffset0(section);

    NNS_FndAppendListObject(&heap->sectionList, section);

    return TRUE;
}
