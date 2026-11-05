#ifndef GAME_HEAP_H
#define GAME_HEAP_H

/* The game's heaps.
 *
 * Everything the game allocates comes from two NitroSystem expanded heaps that
 * Ov001_CreateMainAndSubHeaps makes from the main arena: the main heap, 0xc8000 bytes from its low
 * end, and the sub heap, the rest up to HW_MAIN_MEM_MAIN_END (half of it under DS Protect's
 * emulator or flashcart answer). Ov001_InitGameHeaps keeps each with an allocator over it in a
 * GameHeap (gMainHeapHandle, gSubHeapHandle), points gMainHeap and gSubHeap at them and makes the
 * sub heap current (gCurrentHeap). HeapState_Recreate remakes one over its own region. Sizes are
 * u32, as NitroSystem gives them. */

#include "nitro/types.h"

struct NNSiFndHeapHead;

typedef struct GameHeap {
    struct NNSiFndHeapHead *handle;  /* 0x00: the expanded heap (NNSFndHeapHandle) */
    u32 allocator[4];                /* 0x04: an NNSFndAllocator over it, 4-byte aligned */
} GameHeap;

/* The current heap; Heap_SetCurrent(0) makes the sub heap current. Each returns the previous one. */
GameHeap *Heap_GetCurrent(void);
GameHeap *Heap_SetCurrent(GameHeap *heap);

/* 4-byte-aligned memory from `heap`, or from the current heap for 0. */
void *AllocFromExpHeapWrapper(u32 size, GameHeap *heap);

/* The same with the given alignment; a block back to `heap` (0: the current heap); a block resized
 * in place. ExpHeap_Free gives NNS_FndFreeToExpHeap's r0 back. */
void *ExpHeap_AllocOrDefault(u32 size, int alignment, GameHeap *heap);
int ExpHeap_Free(void *block, GameHeap *heap);
u32 ExpHeap_ResizeBlock(GameHeap *heap, void *memoryBlock, u32 size);

/* Frees a font resource's data; returns what the sub heap can still allocate. */
u32 FontResource_Destroy(void *font);

#endif
