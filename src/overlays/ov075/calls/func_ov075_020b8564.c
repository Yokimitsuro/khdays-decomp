extern void func_ov075_020b98bc(int self);
extern void func_ov075_020b8814(int a, int b, int c);
extern void func_ov075_020b8870(int a, int b);
extern int func_ov022_020912d8(int a);
extern int func_02030788(void);
extern int data_ov075_020b9e20;

void func_ov075_020b8564(int self) {
    char *blk = (char *)(*(int *)&data_ov075_020b9e20 + 0x194);
    func_ov075_020b98bc(self);
    func_ov075_020b8814(self, (int)(blk + 0x2c00), *(short *)(self + 0x2a00 + 0xba));
    func_ov075_020b8870(self, (int)(blk + 0x2c00));
    if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644) + 0x30) != 0) {
        if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644) + 0x60) != 0) return;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
}
