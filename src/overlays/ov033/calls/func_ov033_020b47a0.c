extern void func_ov033_020b4a60(int a);
extern void func_0201571c(void);
extern void func_01ff9f00(int a, int b, int c);
extern void func_020279e0(int a);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov033_020b47a0(int self, int blk) {
    int i;
    char *p;
    if (!((Flags *)(self + 0x694))->b0) return;
    p = (char *)(blk + 0x118);
    for (i = 0; i < 6; i++, p += 0x110) {
        func_ov033_020b4a60((int)p);
    }
    if (*(int *)blk != 1) return;
    func_0201571c();
    func_01ff9f00(0x17, blk + 0x8c, 0xc);
    func_020279e0(blk + 0x2c);
}
