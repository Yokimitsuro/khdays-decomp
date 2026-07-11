extern void func_0202a7dc(void *);

void func_ov044_020b3b10(char *obj) {
    int i = 0;
    char *p = obj + 0x234;
    for (; i < 8; i++) {
        func_0202a7dc(p);
        p += 0x170;
    }
}
