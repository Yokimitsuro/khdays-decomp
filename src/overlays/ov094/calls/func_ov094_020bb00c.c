extern void func_ov094_020bb700(int a, int b);
extern void func_ov094_020bb328(int a, int b);
extern void func_ov094_020bb9d0(int a, int b);
extern void func_ov094_020bb56c(int a, int b);
extern void func_ov094_020bb688(int a, int b);

typedef struct { unsigned char b0 : 1; } Flags;

void func_ov094_020bb00c(int self, int a) {
    if (!((Flags *)(self + 0x694))->b0) return;
    func_ov094_020bb700(self, a + 0x228);
    func_ov094_020bb328(self, a);
    func_ov094_020bb9d0(self, a + 0x118);
    func_ov094_020bb56c(self, a + 0x338);
    func_ov094_020bb688(self, a + 0x444);
}
