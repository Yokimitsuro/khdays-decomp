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

#define NNS_FND_FRMHEAP_FREE_HEAD (1 << 0)
#define NNS_FND_FRMHEAP_FREE_TAIL (1 << 1)

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
extern void func_02010b48 (NNSiFndHeapHead * pHeapHd);
extern void func_02010b5c (NNSiFndHeapHead * pHeapHd);

/* func_02010c00 -- NitroSystem frameheap.c: NNS_FndFreeToFrmHeap. */
void func_02010c00 (NNSFndHeapHandle heap, int mode)
{

    if (mode & NNS_FND_FRMHEAP_FREE_HEAD) {
        func_02010b48(heap);
    }

    if (mode & NNS_FND_FRMHEAP_FREE_TAIL) {
        func_02010b5c(heap);
    }
}
