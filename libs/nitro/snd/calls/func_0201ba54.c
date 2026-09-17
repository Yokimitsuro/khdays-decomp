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
void NNS_FndRemoveListObject(NNSFndList * list, void * object);
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
BOOL func_02010c2c(NNSFndHeapHandle heap, u32 tagName);
BOOL func_02010c7c(NNSFndHeapHandle heap, u32 tagName);
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndHeap;
typedef void (*NNSSndHeapDisposeCallback)(void * mem, u32 size, u32 data1, u32 data2);
typedef struct NNSSndHeap * NNSSndHeapHandle;
void func_0201b8e4(NNSSndHeapHandle heap);
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
extern BOOL func_0201bb6c(NNSSndHeap * heap);
extern void func_0201bba8(void);
extern void func_0201b8e4 (NNSSndHeapHandle heap);
extern BOOL func_0201bb6c (NNSSndHeap * heap);
extern void func_0201bba8 (void);

/* func_0201ba54 -- NitroSystem heap.c: NNS_SndHeapLoadState. */
void func_0201ba54 (NNSSndHeapHandle heap, int level)
{
    NNSSndHeapSection * section;
    void * object = NULL;
    BOOL result;
    BOOL doCallback = FALSE;


    if (level == 0) {
        func_0201b8e4(heap);
        return;
    }

    while (level < heap->sectionList.numObjects) {
        section = (NNSSndHeapSection *)NNS_FndGetPrevListObject(&heap->sectionList, NULL);

        while ((object = NNS_FndGetPrevListObject(&section->blockList, object)) != NULL) {
            NNSSndHeapBlock * block = (NNSSndHeapBlock *)object;
            if (block->callback != NULL) {
                block->callback(block->buffer, block->size, block->data1, block->data2);
                doCallback = TRUE;
            }
        }

        NNS_FndRemoveListObject(&heap->sectionList, section);
    }

    result = func_02010c7c(heap->handle, (u32)level);

    if (doCallback) func_0201bba8();

    result = func_02010c2c(heap->handle, heap->sectionList.numObjects);

    result = func_0201bb6c(heap);
}
