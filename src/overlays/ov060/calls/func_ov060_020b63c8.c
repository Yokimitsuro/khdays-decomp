extern void func_ov060_020b6484(int a, int b, int c);
extern void func_ov060_020b65fc(int a, int b, int c);
extern void func_ov060_020b68f8(int a, int b, int c);
extern void func_ov060_020b6b20(int a, int b, int c);

void func_ov060_020b63c8(int a0, int a1, int a2) {
    func_ov060_020b6484(a0, a1, a2);
    func_ov060_020b65fc(a0, a1, a2);
    func_ov060_020b68f8(a0, a1 + 0x110, a2);
    func_ov060_020b6b20(a0, a1 + 0x220, a2);
}
