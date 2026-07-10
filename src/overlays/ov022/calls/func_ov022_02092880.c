extern int func_0201ef9c(void *arg0, int arg1, int arg2, int arg3);
extern void NNSi_FndFreeFromDefaultHeap(int arg0);
extern int data_ov022_020b2b88;

void func_ov022_02092880(unsigned char *arg0, int arg1, int arg2, int arg3) {
    if (0 < arg1) {
        int x = func_0201ef9c(&data_ov022_020b2b88, 6, arg2, arg3);
        int base;
        if (9 < arg1) arg1 = 9;
        base = x + (arg1 - 1) * 8;
        *(unsigned short *)(arg0 + 2) = *(unsigned short *)base;
        *(unsigned short *)(arg0 + 4) = *(unsigned short *)(base + 2);
        *(unsigned short *)(arg0 + 6) = *(unsigned short *)(base + 4);
        *(unsigned short *)(arg0 + 8) = *(unsigned short *)(base + 6);
        NNSi_FndFreeFromDefaultHeap(x);
        *arg0 = *arg0 | 1;
    }
}
