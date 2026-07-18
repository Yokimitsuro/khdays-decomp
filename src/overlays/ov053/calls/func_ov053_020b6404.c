extern void func_02014dc4(int a, int b);

typedef struct { int a[3]; } Idx3;
extern Idx3 data_ov053_020b7d70;

void func_ov053_020b6404(int self) {
    char *blk = (char *)(self + 0xf10);
    Idx3 idx = data_ov053_020b7d70;
    int i;
    for (i = 0; i < 3; i++) {
        if (*(int *)(blk + idx.a[i] * 4 + 0xc) != 0) {
            func_02014dc4((int)(blk + 0x20), *(int *)(blk + idx.a[i] * 4 + 0xc));
            *(int *)(blk + idx.a[i] * 4 + 0xc) = 0;
        }
        *(short *)(blk + idx.a[i] * 2 + 2) = -1;
    }
}
