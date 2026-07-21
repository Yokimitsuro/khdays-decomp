extern int NNSi_FndFreeFromDefaultHeap(int block);
/* Release the two optional side buffers (obj+0x28 / obj+0x2c), each gated on its own size field
 * (obj+0x30 / obj+0x34); returns 1. */
int func_ov002_02052464(int obj) {
    if (*(int *)(obj + 0x30) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(obj + 0x28));
    }
    if (*(int *)(obj + 0x34) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(obj + 0x2c));
    }
    return 1;
}
