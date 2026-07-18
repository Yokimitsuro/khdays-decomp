extern int func_02030788(void);
extern int func_ov022_020a35f4(int *self, int state);
extern int data_ov085_020b9260;

int func_ov085_020b8d14(int *self, int v) {
    int *blk = (int *)(*(int *)&data_ov085_020b9260 + 0xc50 + 0x2000);
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    blk[0] = v;
    blk[1] = 1;
    *(int *)((char *)blk + 0x120) = 0;
    blk[2] = 0;
    *(int *)((char *)blk + 0x124) = 0;
    return func_ov022_020a35f4(self, 0x21);
}
