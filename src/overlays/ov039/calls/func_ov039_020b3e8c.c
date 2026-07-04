extern void func_ov039_020b3f54();
extern void func_ov039_020b4168();

void func_ov039_020b3e8c(int this_, int arg1, int arg2) {
    int i;
    char *p = (char *)(arg1 + 0x18);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_ov039_020b3f54(this_, (int)p, arg2);
    }
    func_ov039_020b4168(this_, arg1 + 0x308, arg2);
}
