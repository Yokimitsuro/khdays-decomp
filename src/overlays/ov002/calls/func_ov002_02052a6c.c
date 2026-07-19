extern void *NNSi_FndAllocFromDefaultExpHeap(int size);
extern void MI_CpuFill8(void *p, int v, int n);
extern int func_0200ff54(char *s);
extern char *func_0200ff20(char *dst, char *src);
extern void NNS_FndAppendListObject(void *list, void *obj);

extern int data_ov002_0207f608;

/* Append a new 0x20-byte entry to the global list.
 *
 * `key` is TAGGED by its top bit: with bit31 SET it is an inline value and is
 * stored as-is; with bit31 CLEAR it is a `char *` and the string is duplicated
 * onto the heap (strlen+1, alloc, strcpy).  Either way the result lands in the
 * same slot, so consumers must test the tag before dereferencing it.
 * That is why the ROM materialises 0x80000000 and uses TST rather than a sign
 * test -- it is a mask on a union, not an arithmetic comparison. */
void func_ov002_02052a6c(int key, int arg1, int arg2) {
    int *node;
    char *copy;

    node = (int *)NNSi_FndAllocFromDefaultExpHeap(0x20);
    MI_CpuFill8(node, 0, 0x20);
    if ((key & 0x80000000) != 0) {
        node[1] = key;
    } else {
        copy = (char *)NNSi_FndAllocFromDefaultExpHeap(func_0200ff54((char *)key) + 1);
        node[1] = (int)copy;
        func_0200ff20(copy, (char *)key);
    }
    node[4] = arg1;
    node[3] = arg2;
    NNS_FndAppendListObject(*(void **)&data_ov002_0207f608, node);
}
