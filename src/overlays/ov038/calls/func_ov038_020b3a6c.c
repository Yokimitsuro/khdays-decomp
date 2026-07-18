extern void func_ov038_020b4160(int a, int b);
extern void func_ov038_020b3d88(int a, int b);
extern void func_ov038_020b4430(int a, int b);
extern void func_ov038_020b3fcc(int a, int b);
extern void func_ov038_020b40e8(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov038_020b3a6c(int self, int a) {
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov038_020b4160(self, a + 0x228);
    func_ov038_020b3d88(self, a);
    func_ov038_020b4430(self, a + 0x118);
    func_ov038_020b3fcc(self, a + 0x338);
    func_ov038_020b40e8(self, a + 0x444);
}
