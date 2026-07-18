extern void func_ov077_020b9040(int a, int b);
extern void func_ov077_020b8c68(int a, int b);
extern void func_ov077_020b9310(int a, int b);
extern void func_ov077_020b8eac(int a, int b);
extern void func_ov077_020b8fc8(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov077_020b894c(int self, int a) {
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov077_020b9040(self, a + 0x228);
    func_ov077_020b8c68(self, a);
    func_ov077_020b9310(self, a + 0x118);
    func_ov077_020b8eac(self, a + 0x338);
    func_ov077_020b8fc8(self, a + 0x444);
}
