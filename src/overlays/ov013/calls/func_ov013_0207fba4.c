/* Allocate and seed a 0x1c-byte task node: two id bytes at +0x18/+0x19, the
 * caller word at +0xc, the counter at +0x14 cleared, and the default step
 * handler in the first callback slot with the other two empty. */
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern void func_ov013_0207fa40(void);

static inline void set_callback(void **slot, void *value) {
    if ((int)value != -1) {
        *slot = value;
    }
}

void *func_ov013_0207fba4(int idA, int idB, int payload) {
    char *node = (char *)NNSi_FndAllocFromDefaultExpHeap(0x1c);

    node[0x18] = (char)idA;
    node[0x19] = (char)idB;
    *(int *)(node + 0xc) = payload;
    *(int *)(node + 0x14) = 0;

    set_callback((void **)(node + 0), (void *)func_ov013_0207fa40);
    set_callback((void **)(node + 4), (void *)0);
    set_callback((void **)(node + 8), (void *)0);

    return node;
}
