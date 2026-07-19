extern void func_ov046_020b41a4(int a, char *b, int c);
extern int func_ov046_020b445c(int a, int b);
extern int func_02030788(void);

void func_ov046_020b4088(int self, char *blk, int arg) {
    int i;
    int any = 0;
    char *p;
    if (*(int *)(blk + 0x110) != 0) any = 1;
    func_ov046_020b41a4(self, blk, arg);
    for (i = 0, p = blk + 0x128; i < 6; i++, p += 0x120) {
        if (func_ov046_020b445c((int)p, arg) == 0) any = 1;
    }
    if (any == 0) return;
    if (func_02030788() == 0) {
        *(long long *)((char *)self + 0x464) |= 0x10000;
    }
    if (func_02030788() != 0) return;
    *(long long *)((char *)self + 0x46c) |= 0x10000;
}
