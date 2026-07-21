extern int NNSi_FndFreeFromDefaultHeap(int block);
extern char *data_ov002_0207fa00;
void func_ov002_0206a27c(void) {
    int *slot = (int *)((int)data_ov002_0207fa00 + 0x8d14);
    if (*slot != 0) {
        NNSi_FndFreeFromDefaultHeap(*slot);
        *slot = 0;
    }
}
