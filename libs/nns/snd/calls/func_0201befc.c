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


#define NNS_FND_HEAP_INVALID_HANDLE NULL
#define NNS_SND_HEAP_INVALID_HANDLE NNS_FND_HEAP_INVALID_HANDLE
#define RESERVED_AREASIZE 32

void DC_StoreRange(const void * startAddr, u32 nBytes);
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
typedef int (*MIDeviceReadFunction)(void * userdata, void * buffer, u32 offset, u32 length);
typedef int (*MIDeviceWriteFunction)(void * userdata, const void * buffer, u32 offset, u32 length);
struct NNSSndHeap;
typedef void (*NNSSndHeapDisposeCallback)(void * mem, u32 size, u32 data1, u32 data2);
typedef struct NNSSndHeap * NNSSndHeapHandle;
void * func_0201b9a0(NNSSndHeapHandle heap, u32 size, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2);
s32 func_0201b6f4(u32 fileId, void * buffer, s32 size, s32 offset);
u32 func_0201b6cc(u32 fileId);

/* func_0201befc -- NitroSystem sndarc_loader.c: NNSi_SndArcLoadFile. */
void * func_0201befc (u32 fileId, NNSSndHeapDisposeCallback callback, u32 data1, u32 data2, NNSSndHeapHandle heap)
{
    void * buffer;
    u32 len;

    len = func_0201b6cc(fileId);
    if (len == 0) return NULL;

    if (heap == NNS_SND_HEAP_INVALID_HANDLE) return NULL;

    buffer = func_0201b9a0(heap, len + RESERVED_AREASIZE, callback, data1, data2);
    if (buffer == NULL) return NULL;

    if (func_0201b6f4(fileId, buffer, (s32)len, 0) != len) {
        return NULL;
    }

    DC_StoreRange(buffer, len);

    return buffer;
}
