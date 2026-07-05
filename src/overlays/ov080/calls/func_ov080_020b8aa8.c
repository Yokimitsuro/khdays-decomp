extern void func_ov080_020b8b64(int a, int b, int c);
extern void func_ov080_020b8cdc(int a, int b, int c);
extern void func_ov080_020b8fd8(int a, int b, int c);
extern void func_ov080_020b9200(int a, int b, int c);

void func_ov080_020b8aa8(int a0, int a1, int a2) {
    func_ov080_020b8b64(a0, a1, a2);
    func_ov080_020b8cdc(a0, a1, a2);
    func_ov080_020b8fd8(a0, a1 + 0x110, a2);
    func_ov080_020b9200(a0, a1 + 0x220, a2);
}
