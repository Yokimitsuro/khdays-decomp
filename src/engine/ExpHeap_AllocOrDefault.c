/* Allocates memory with the given alignment from the given game heap's expanded heap, or from the
 * current heap when none is given. */

#include "game/heap.h"

extern void *NNS_FndAllocFromExpHeapEx(struct NNSiFndHeapHead *heap, u32 size, int alignment);
extern GameHeap *gCurrentHeap;

void *ExpHeap_AllocOrDefault(u32 size, int alignment, GameHeap *heap) {
    if (heap == 0) heap = gCurrentHeap;
    return NNS_FndAllocFromExpHeapEx(heap->handle, size, alignment);
}
