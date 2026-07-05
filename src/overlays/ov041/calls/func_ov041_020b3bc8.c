extern void func_ov041_020b3c84(int a, int b, int c);
extern void func_ov041_020b3dfc(int a, int b, int c);
extern void func_ov041_020b40f8(int a, int b, int c);
extern void func_ov041_020b4320(int a, int b, int c);

void func_ov041_020b3bc8(int a0, int a1, int a2) {
    func_ov041_020b3c84(a0, a1, a2);
    func_ov041_020b3dfc(a0, a1, a2);
    func_ov041_020b40f8(a0, a1 + 0x110, a2);
    func_ov041_020b4320(a0, a1 + 0x220, a2);
}
