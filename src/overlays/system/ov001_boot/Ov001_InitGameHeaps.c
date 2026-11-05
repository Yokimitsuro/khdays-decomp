/* Creates the main and sub expanded heaps and their allocators, points gMainHeap and gSubHeap at
 * them and makes the sub heap current (game/heap.h). */

#include "game/heap.h"

extern void Ov001_CreateMainAndSubHeaps(struct NNSiFndHeapHead **outMainHeap, struct NNSiFndHeapHead **outSubHeap);
extern void NNS_FndInitAllocatorForExpHeap(void *allocator, struct NNSiFndHeapHead *heap, int align);
extern GameHeap *gMainHeap;
extern GameHeap *gCurrentHeap;
extern GameHeap *gSubHeap;
extern struct NNSiFndHeapHead *gSubHeapHandle;
extern int gSubHeapAllocator;
extern struct NNSiFndHeapHead *gMainHeapHandle;
extern int gMainHeapAllocator;

void Ov001_InitGameHeaps(void) {
    struct NNSiFndHeapHead *mainHeap;
    struct NNSiFndHeapHead *subHeap;

    Ov001_CreateMainAndSubHeaps(&mainHeap, &subHeap);
    gMainHeapHandle = mainHeap;
    NNS_FndInitAllocatorForExpHeap(&gMainHeapAllocator, mainHeap, 4);
    gMainHeap = (GameHeap *)&gMainHeapHandle;
    gSubHeapHandle = subHeap;
    NNS_FndInitAllocatorForExpHeap(&gSubHeapAllocator, subHeap, 4);
    gSubHeap = (GameHeap *)&gSubHeapHandle;
    gCurrentHeap = (GameHeap *)&gSubHeapHandle;
}
