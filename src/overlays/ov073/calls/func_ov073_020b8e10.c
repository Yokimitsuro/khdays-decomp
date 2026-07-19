extern int func_02030788(void);
extern int func_02023c40(void);
extern int func_ov022_020a35f4(int *self, int state);
extern int data_ov073_020ba540;

int func_ov073_020b8e10(int *self) {
    int *blk = (int *)(*(int *)&data_ov073_020ba540 + 0xe4 + 0x2c00);
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    blk[5] = (func_02023c40() == 1) ? 0x1333 : 0xccd;
    blk[6] = (func_02023c40() == 1) ? 0x600 : 0x400;
    return func_ov022_020a35f4(self, 0x21);
}
