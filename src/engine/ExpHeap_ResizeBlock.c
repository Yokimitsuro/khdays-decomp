/* Resizes a memory block of a game heap's expanded heap (NNS_FndResizeForMBlockExpHeap). */

#include "game/heap.h"

extern u32 NNS_FndResizeForMBlockExpHeap(struct NNSiFndHeapHead *heap, void *memoryBlock, u32 size);

u32 ExpHeap_ResizeBlock(GameHeap *heap, void *memoryBlock, u32 size) {
    return NNS_FndResizeForMBlockExpHeap(heap->handle, memoryBlock, size);
}
