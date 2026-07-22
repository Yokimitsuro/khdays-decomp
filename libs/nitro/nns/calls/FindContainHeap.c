/* Depth-first search for the innermost heap whose [start,end) range contains `p`.
 *
 * The recursive result is RETURNED when it is non-null (the ROM's `moveq r0,r4` is
 * followed by an unconditional pop, not a `popeq`), so the child heap wins over its
 * parent; written as `if (child == 0) return heap;` mwcc predicates the return instead. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);

void *FindContainHeap(void *list, char *p) {
    char *heap = NNS_FndGetNextListObject(list, 0);
    while (heap != 0) {
        if (*(char **)(heap + 0x18) <= p && p < *(char **)(heap + 0x1c)) {
            char *inner = FindContainHeap(heap + 0xc, p);
            if (inner == 0) {
                inner = heap;
            }
            return inner;
        }
        heap = NNS_FndGetNextListObject(list, heap);
    }
    return 0;
}
