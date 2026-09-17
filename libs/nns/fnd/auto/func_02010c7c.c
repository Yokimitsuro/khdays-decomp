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
typedef struct NNSiFndFrmHeapState NNSiFndFrmHeapState;
struct NNSiFndFrmHeapState {
    u32 tagName;
    void * headAllocator;
    void * tailAllocator;
    NNSiFndFrmHeapState * pPrevState;
};
typedef struct NNSiFndFrmHeapHead NNSiFndFrmHeapHead;
struct NNSiFndFrmHeapHead {
    void * headAllocator;
    void * tailAllocator;
    NNSiFndFrmHeapState * pState;
};
typedef u32 NNSiUIntPtr;
inline NNSiUIntPtr NNSiGetUIntPtr(const void* ptr)
{
    return (NNSiUIntPtr)ptr;
}
inline void* AddU32ToPtr(void* ptr, u32 val)
{
    return (void*)( NNSiGetUIntPtr(ptr) + val );
}
static inline NNSiFndFrmHeapHead * GetFrmHeapHeadPtrFromHeapHead (NNSiFndHeapHead * pHHead)
{
    return AddU32ToPtr(pHHead, sizeof(NNSiFndHeapHead));
}

/* func_02010c7c -- NitroSystem frameheap.c: NNS_FndFreeByStateToFrmHeap. */
BOOL func_02010c7c (NNSFndHeapHandle heap, u32 tagName)
{

    {
        NNSiFndFrmHeapHead * pFrmHeapHd = GetFrmHeapHeadPtrFromHeapHead(heap);
        NNSiFndFrmHeapState * pState = pFrmHeapHd->pState;

        if (tagName != 0) {
            for (; pState; pState = pState->pPrevState)
            {
                if (pState->tagName == tagName)
                    break;
            }
        }

        if (!pState) {
            return FALSE;
        }

        pFrmHeapHd->headAllocator = pState->headAllocator;
        pFrmHeapHd->tailAllocator = pState->tailAllocator;

        pFrmHeapHd->pState = pState->pPrevState;

        return TRUE;
    }
}
