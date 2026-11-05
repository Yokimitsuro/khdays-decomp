/* Returns the current heap (gCurrentHeap). */

#include "game/heap.h"

extern GameHeap *gCurrentHeap;

GameHeap *Heap_GetCurrent(void) {
    return gCurrentHeap;
}
