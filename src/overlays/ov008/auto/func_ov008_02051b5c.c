struct S {
    int a;       /* 0x00 */
    int pad1;    /* 0x04 */
    int pad2;    /* 0x08 */
    int c;       /* 0x0c */
    char rest[0xdc - 0x10];
};

int func_ov008_02051b5c(struct S *p) {
    int i;
    if (p->a != 0xf0) {
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (p->a < 0) {
            break;
        }
        if (p->a == 0xfb) {
            if (p->c >= 3) {
                return 1;
            }
        }
        p++;
    }
    return 0;
}
