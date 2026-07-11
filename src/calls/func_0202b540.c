/* Push `node` onto the head of the intrusive list at
 * *(data_0204c208 + index*4 + 0x84); links prev/next and tags node[0xa]. */
extern int data_0204c208;
void func_0202b540(int index, void *node) {
    int base = data_0204c208;
    void *old = *(void **)(base + index * 4 + 0x84);
    if (old != 0) {
        *(void **)node = old;
        *(void **)((char *)old + 4) = node;
    }
    *(void **)(base + index * 4 + 0x84) = node;
    *((char *)node + 0xa) = (char)index;
}
