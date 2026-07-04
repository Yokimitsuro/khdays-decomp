extern void func_ov078_020b8e34();
extern void func_ov078_020b9048();

void func_ov078_020b8d6c(int this_, int arg1, int arg2) {
    int i;
    char *p = (char *)(arg1 + 0x18);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_ov078_020b8e34(this_, (int)p, arg2);
    }
    func_ov078_020b9048(this_, arg1 + 0x308, arg2);
}
