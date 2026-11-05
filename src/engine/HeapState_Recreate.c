/* Destroys a game heap's expanded heap and recreates it over the same region (its start up to the
 * heap head's heapEnd, +0x1c) with a new allocator. Scene_AdvanceToPending empties the sub heap
 * this way between scenes. */

#include "game/heap.h"

extern void NNS_FndDestroyExpHeap(void *heap);
extern void *NNS_FndCreateExpHeapEx(void *start, unsigned int size, int opt);
extern void NNS_FndInitAllocatorForExpHeap(void *allocator, void *heap, int align);

void HeapState_Recreate(GameHeap *heap) {
    char *old = (char *)heap->handle;
    unsigned int size = (unsigned int)(((char **)old)[7] - old);
    NNS_FndDestroyExpHeap(old);
    heap->handle = NNS_FndCreateExpHeapEx(old, size, 1);
    NNS_FndInitAllocatorForExpHeap(heap->allocator, heap->handle, 4);
}
