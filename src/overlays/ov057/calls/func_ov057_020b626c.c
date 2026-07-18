extern void func_ov057_020b6960(int a, int b);
extern void func_ov057_020b6588(int a, int b);
extern void func_ov057_020b6c30(int a, int b);
extern void func_ov057_020b67cc(int a, int b);
extern void func_ov057_020b68e8(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov057_020b626c(int self, int a) {
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov057_020b6960(self, a + 0x228);
    func_ov057_020b6588(self, a);
    func_ov057_020b6c30(self, a + 0x118);
    func_ov057_020b67cc(self, a + 0x338);
    func_ov057_020b68e8(self, a + 0x444);
}
