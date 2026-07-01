extern int func_0203c960();
extern int func_0203ca9c();
extern int func_0203ca30();
extern int func_0203bc78();

void func_ov142_020d2490(char *r7, int r6) {
    int *r4;
    int i;
    int *p;

    r4 = *(int **)(r7 + 0x84);
    func_0203c960(r7 + 0x30);
    for (i = 0; i < 0x10; i++) {
        p = (int *)r4[i + 2];
        if (p == 0) {
            return;
        }
        func_0203ca9c(r7 + 0x30, p[0x20] << 1);
        func_0203ca30(r7 + 0x30, (char *)r4[i + 2] + 0x74);
        func_0203bc78(r7, r6);
    }
}
