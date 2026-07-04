extern void func_ov098_020bbbfc();

void func_ov098_020bb99c(int this_, int base) {
    int i;
    char *p = (char *)(base + 0x14);
    for (i = 0; i < 7; i++) {
        func_ov098_020bbbfc(p);
        p += 0x10c;
    }
}
