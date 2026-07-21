extern int NNSi_FndFreeFromDefaultHeap(int block);
extern char *data_ov002_0207fa00;
/* Free the buffer at rootCtx+0x8d7c and null the slot, if allocated. */
void func_ov002_0206e184(void) {
    int *slot = (int *)((int)data_ov002_0207fa00 + 0x8d7c);
    if (*slot != 0) {
        NNSi_FndFreeFromDefaultHeap(*slot);
        *slot = 0;
    }
}
