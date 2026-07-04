extern void func_ov095_020bb4f4();
extern void func_ov095_020bb708();

void func_ov095_020bb42c(int this_, int arg1, int arg2) {
    int i;
    char *p = (char *)(arg1 + 0x18);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_ov095_020bb4f4(this_, (int)p, arg2);
    }
    func_ov095_020bb708(this_, arg1 + 0x308, arg2);
}
