extern void func_ov061_020b6e5c();

void func_ov061_020b6bfc(int this_, int base) {
    int i;
    char *p = (char *)(base + 0x14);
    for (i = 0; i < 7; i++) {
        func_ov061_020b6e5c(p);
        p += 0x10c;
    }
}
