/* Drop the pending edit: only a kind-2 edit owns the buffer at +0x2c, so only
 * that kind frees it and clears the kind byte. The object at +0x24 is notified
 * either way when there is one. Always reports 0. */
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_ov002_02065304(int object);

extern char *data_ov002_0207f638;

int func_ov002_02065638(void) {
    char *ctx = data_ov002_0207f638;

    if (*(unsigned char *)(ctx + 0x28) == 2) {
        void *buffer = *(void **)(ctx + 0x2c);

        if (buffer != 0) {
            NNSi_FndFreeFromDefaultHeap(buffer);
            *(int *)(ctx + 0x2c) = 0;
        }
        *(unsigned char *)(ctx + 0x28) = 0;
    }

    if (*(int *)(ctx + 0x24) != 0) {
        func_ov002_02065304(*(int *)(ctx + 0x24));
    }

    return 0;
}
