extern int *NNSi_AllocFromHeadOfExpHeap(void *heap, int size, int align);

/* Allocate a 4-word record from the list's ExpHeap (at list+0x24) and push it
   as the new head (list+0x2c), carrying its payload and prior links. */
int func_02010c2c(int list, int payload) {
    int heapCursor = *(int *)(list + 0x24);
    int *node = NNSi_AllocFromHeadOfExpHeap((void *)(list + 0x24), 0x10, 4);
    if (node != 0) {
        node[0] = payload;
        node[1] = heapCursor;
        node[2] = *(int *)(list + 0x28);
        node[3] = *(int *)(list + 0x2c);
        *(int **)(list + 0x2c) = node;
        return 1;
    }
    return 0;
}
