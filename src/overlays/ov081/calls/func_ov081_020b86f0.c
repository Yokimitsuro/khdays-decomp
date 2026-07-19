extern int func_02030788(void);
extern int func_ov022_02095554(int a);
extern int func_ov022_020912d8(int a);
extern int func_ov022_020a35f4(int self, int state);
extern int data_ov081_020b96e0;

int func_ov081_020b86f0(int self) {
    int ret = 0;
    int *blk = (int *)(*(int *)&data_ov081_020b96e0 + 0x2c + 0x2c00);
    int ok = 1;
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    blk[2] = func_ov022_02095554(self + 0x2f8 + 0x2000);
    if (blk[2] != 0) {
        if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644) + 0x30) == 0) {
            ok = 0;
        }
    }
    if (ok != 0) {
        ret = func_ov022_020a35f4(self, 0x21);
    }
    return ret;
}
