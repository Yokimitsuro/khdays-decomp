extern int func_02030788(void);
extern int func_ov022_020a35f4(int *self, int state);
extern int data_ov037_020b4e20;

int func_ov037_020b3c70(int *self, int alt) {
    char *blk = (char *)(*(int *)&data_ov037_020b4e20 + 0x2c + 0x2c00);
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    *(int *)(blk + 0x114) = alt;
    if (alt != 0) {
        return func_ov022_020a35f4(self, 0x22);
    }
    return func_ov022_020a35f4(self, 0x21);
}
