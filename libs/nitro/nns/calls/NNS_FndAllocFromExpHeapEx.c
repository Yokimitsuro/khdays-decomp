/* Rounds the request up to a word and allocates from the head (positive alignment) or the
 * tail (negative alignment) of the expanded heap. */
extern void *AllocFromHead(void *heap, unsigned int size, int align);
extern void *AllocFromTail(void *heap, unsigned int size, int align);

void *NNS_FndAllocFromExpHeapEx(void *heap, unsigned int size, int align) {
    if (size == 0) {
        size = 1;
    }
    size = (size + 3) & ~3u;
    if (align >= 0) {
        return AllocFromHead(heap, size, align);
    }
    return AllocFromTail(heap, size, -align);
}
