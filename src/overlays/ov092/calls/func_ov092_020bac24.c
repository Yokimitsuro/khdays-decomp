extern void func_ov092_020bbf7c(int self);
extern void func_ov092_020baed4(int a, int b, int c);
extern void func_ov092_020baf30(int a, int b);
extern int func_ov022_020912d8(int a);
extern int func_02030788(void);
extern int data_ov092_020bc4e0;

void func_ov092_020bac24(int self) {
    char *blk = (char *)(*(int *)&data_ov092_020bc4e0 + 0x194);
    func_ov092_020bbf7c(self);
    func_ov092_020baed4(self, (int)(blk + 0x2c00), *(short *)(self + 0x2a00 + 0xba));
    func_ov092_020baf30(self, (int)(blk + 0x2c00));
    if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644) + 0x30) != 0) {
        if (func_ov022_020912d8(*(int *)(self + 0x2000 + 0x644) + 0x60) != 0) return;
    }
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
}
