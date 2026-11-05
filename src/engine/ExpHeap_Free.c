/* Frees a block to the given game heap's expanded heap, or to the current heap when none is
 * given. */

#include "game/heap.h"

extern int NNS_FndFreeToExpHeap(struct NNSiFndHeapHead *heap, void *block);
extern GameHeap *gCurrentHeap;

int ExpHeap_Free(void *block, GameHeap *heap) {
    if (heap == 0) heap = gCurrentHeap;
    return NNS_FndFreeToExpHeap(heap->handle, block);
}
