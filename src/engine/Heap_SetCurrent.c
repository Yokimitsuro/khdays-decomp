/* Makes a heap current (the sub heap, gSubHeap, for 0) and returns the previous one; callers
 * bracket work in a scoped heap with two calls. */

#include "game/heap.h"

extern GameHeap *gCurrentHeap;  /* gSubHeap follows it */

GameHeap *Heap_SetCurrent(GameHeap *heap) {
    GameHeap *previous = gCurrentHeap;
    gCurrentHeap = (heap == 0) ? (&gCurrentHeap)[1] : heap;
    return previous;
}
