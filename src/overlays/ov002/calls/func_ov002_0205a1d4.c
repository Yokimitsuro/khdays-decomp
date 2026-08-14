/* Release one entry of the pool: optionally hand its request back first, unlink
 * it from the pool's list, free its two payload buffers, then free the entry.
 *
 * The pool is carried as Ov002EntryPool in Ghidra and its list head is formed as
 * the pool plus 0x10, matching func_ov002_02059dc8, which is the teardown that
 * walks the list and calls this for every entry.
 */
extern char *data_ov002_0207f61c;
extern void NNS_FndRemoveListObject(void *list, void *node);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov002_020535f0(int entry);

void func_ov002_0205a1d4(char *node, int notify) {
    char *self = data_ov002_0207f61c;

    if (notify != 0) {
        func_ov002_020535f0(*(int *)(node + 0x20));
    }
    NNS_FndRemoveListObject(self + 0x10, node);

    if (*(void **)(node + 0x10) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(node + 0x10));
        *(void **)(node + 0x10) = 0;
    }
    if (*(void **)(node + 0x14) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(node + 0x14));
        *(void **)(node + 0x14) = 0;
    }
    if (node != 0) {
        NNSi_FndFreeFromDefaultHeap(node);
    }
}
