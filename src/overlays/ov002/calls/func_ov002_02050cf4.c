extern int NNSi_FndFreeFromDefaultHeap(int block);
/* Free the buffer at obj+0x2c (if any), null it, and clear the top three status bits (0xe0) at obj+0x2a. */
int func_ov002_02050cf4(int obj) {
    if (*(int *)(obj + 0x2c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(int *)(obj + 0x2c));
        *(int *)(obj + 0x2c) = 0;
    }
    *(unsigned char *)(obj + 0x2a) &= ~0xe0;
    return 1;
}
