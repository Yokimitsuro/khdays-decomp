extern int func_02030788(void);
extern int func_ov022_020a35f4(int *self, int state);

int func_ov080_020b92d8(int *self, int alt) {
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    if (alt != 0) {
        return func_ov022_020a35f4(self, 0x22);
    }
    return func_ov022_020a35f4(self, 0x21);
}
