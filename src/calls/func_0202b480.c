/* Push `node` onto the head of the intrusive list at
 * *(data_0204c208 + index*4 + 0x64); links prev/next and tags node[0xa].
 * Sibling of func_0202b540 (offset 0x64 vs 0x84); this one re-reads the
 * base pointer for the store rather than caching it. */
extern int data_0204c208;
void func_0202b480(int index, void *node) {
    void *old = *(void **)(data_0204c208 + index * 4 + 0x64);
    if (old != 0) {
        *(void **)node = old;
        *(void **)((char *)old + 4) = node;
    }
    *(void **)(data_0204c208 + index * 4 + 0x64) = node;
    *((char *)node + 0xa) = (char)index;
}
