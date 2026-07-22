/* Allocate a 0x10-byte step node, zero it, store the caller's callback in its
 * first word and append it to the menu root's list at +0xa4. Returns the node. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void NNS_FndAppendListObject(void *list, void *object);

extern char *data_ov002_0207f60c;

void *func_ov002_020538c0(void *callback) {
    void *node = NNSi_FndAllocFromDefaultExpHeap(0x10);

    MI_CpuFill8(node, 0, 0x10);
    *(void **)node = callback;
    NNS_FndAppendListObject(data_ov002_0207f60c + 0xa4, node);
    return node;
}
