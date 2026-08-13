/* Tear the entry pool down: buffers, then every entry still on the list, then the pool itself.
 *
 * The first entry is taken before anything is freed, and inside the loop the NEXT link is read
 * before the current entry is released, which is what makes releasing it safe. The list head is
 * written as the pool plus 0x10 in both places rather than bound to a local, which is how the
 * original forms it once for the first call and then keeps it in the surviving register.
 *
 * Ghidra carries the object as Ov002EntryPool.
 */

extern char *data_ov002_0207f61c;
extern void *NNS_FndGetNextListObject(void *list, void *node);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov002_0205a1d4(void *node, int flag);

void func_ov002_02059dc8(void) {
    char *self = data_ov002_0207f61c;
    void *node = NNS_FndGetNextListObject(self + 0x10, 0);

    if (*(void **)self != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)self);
    }
    if (*(void **)(self + 4) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(self + 4));
    }
    if (node != 0) {
        void *next;

        do {
            next = NNS_FndGetNextListObject(self + 0x10, node);

            func_ov002_0205a1d4(node, 0);
            node = next;
        } while (next != 0);
    }
    data_ov002_0207f61c = 0;
}
