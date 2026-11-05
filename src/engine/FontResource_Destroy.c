/* Frees a font resource's data and returns what the sub heap can still allocate. */

#include "game/heap.h"

extern void NNSi_FndFreeFromDefaultHeap(void *);
extern u32 NNS_FndGetAllocatableSizeForExpHeapEx(struct NNSiFndHeapHead *heap, int alignment);
extern GameHeap *gSubHeap;

u32 FontResource_Destroy(void *font) {
    NNSi_FndFreeFromDefaultHeap(*(void **)((char *)font + 8));
    return NNS_FndGetAllocatableSizeForExpHeapEx(gSubHeap->handle, 4);
}
