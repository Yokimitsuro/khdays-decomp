extern void func_ov042_020b465c();

void func_ov042_020b43fc(int this_, int base) {
    int i;
    char *p = (char *)(base + 0x14);
    for (i = 0; i < 7; i++) {
        func_ov042_020b465c(p);
        p += 0x10c;
    }
}
