extern void func_ov058_020b6754();
extern void func_ov058_020b6968();

void func_ov058_020b668c(int this_, int arg1, int arg2) {
    int i;
    char *p = (char *)(arg1 + 0x18);
    for (i = 0; i < 2; i++, p += 0x10c) {
        func_ov058_020b6754(this_, (int)p, arg2);
    }
    func_ov058_020b6968(this_, arg1 + 0x308, arg2);
}
