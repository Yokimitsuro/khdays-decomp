/* Splice `node` into the intrusive list keyed by index (head table at
 * *(data_0204c208+index*4+0x64)): fix the anchor's prev/next, walk to the
 * list tail, then relink the head slot to the anchor. */
extern int data_0204c208;
void func_0202b4b8(int index, void *node, void **anchor) {
    void *h = anchor[0];
    int base = data_0204c208;
    if (h != 0) *(void **)((char *)h + 4) = node;
    *(void **)node = anchor[0];
    void *tail = node;
    {
        void *p2 = anchor[1];
        *(void **)((char *)node + 4) = p2;
        if (p2 != 0) *(void **)p2 = node;
    }
    if (*(void **)((char *)node + 4) != 0) {
        do {
            tail = *(void **)((char *)tail + 4);
        } while (*(void **)((char *)tail + 4) != 0);
    }
    *(void **)(base + index * 4 + 0x64) = tail;
    {
        void *slot = *(void **)(data_0204c208 + index * 4 + 0x64);
        anchor[0] = slot;
        *(void **)((char *)slot + 4) = anchor;
    }
    anchor[1] = 0;
    *(void **)(base + index * 4 + 0x64) = anchor;
    *((char *)node + 0xa) = (char)index;
}
