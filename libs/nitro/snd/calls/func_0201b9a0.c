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

#define HEAP_ALIGN 32
#define ROUNDUP(value, align) (((u32)(value) + ((align) - 1)) & ~((align) - 1))

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
void * NNS_FndGetPrevListObject(NNSFndList * list, void * object);
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
typedef struct NNSSndHeap * NNSSndHeapHandle;
typedef struct NNSSndHeap {
    NNSFndHeapHandle handle;
    NNSFndList sectionList;
} NNSSndHeap;
typedef struct NNSSndHeapBlock {
    NNSFndLink link;
    u32 size;
    NNSSndHeapDisposeCallback callback;
    u32 data1;
    u32 data2;
    u8 padding[ 0x20 - ((sizeof(NNSFndLink) + sizeof(NNSSndHeapDisposeCallback) + sizeof(u32) * 3) & 0x1f) ];
    u32 buffer[ 0 ];
} NNSSndHeapBlock;
typedef struct NNSSndHeapSection {
    NNSFndList blockList;
    NNSFndLink link;
} NNSSndHeapSection;

/* func_0201b9a0 -- NitroSDK heap.c: NNS_SndHeapAlloc. */
void * func_0201b9a0 (NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2)
{
    NNSSndHeapSection * section;
    NNSSndHeapBlock * block;


    block = (NNSSndHeapBlock *)NNS_FndAllocFromExpHeapEx_0x02010bcc(
        heap->handle, sizeof(NNSSndHeapBlock) + ROUNDUP(size, HEAP_ALIGN), HEAP_ALIGN);
    if (block == NULL) return NULL;

    section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL);

    block->size = size;
    block->callback = callback;
    block->data1 = data1;
    block->data2 = data2;
    NNS_FndAppendListObject(&section->blockList, block);


    return block->buffer;
}
