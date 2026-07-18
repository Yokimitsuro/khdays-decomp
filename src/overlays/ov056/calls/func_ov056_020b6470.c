extern int func_02030788(void);
extern int func_ov022_020a35f4(int *self, int state);
extern int data_ov056_020b7620;

int func_ov056_020b6470(int *self, int alt) {
    char *blk = (char *)(*(int *)&data_ov056_020b7620 + 0x2c + 0x2c00);
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
