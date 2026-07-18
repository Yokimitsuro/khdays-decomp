extern int func_02030788(void);
extern int func_ov022_020a35f4(int *self, int state);
extern int data_ov040_020b4b20;

int func_ov040_020b4258(int *self, int v) {
    int *slot = (int *)(*(int *)&data_ov040_020b4b20 + 0xc50 + 0x2000);
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x46c) |= 0x10000;
    }
    *slot = v;
    return func_ov022_020a35f4(self, 0x21);
}
