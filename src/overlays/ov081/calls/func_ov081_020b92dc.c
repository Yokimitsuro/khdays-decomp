extern void func_ov081_020b953c();

void func_ov081_020b92dc(int this_, int base) {
    int i;
    char *p = (char *)(base + 0x14);
    for (i = 0; i < 7; i++) {
        func_ov081_020b953c(p);
        p += 0x10c;
    }
}
