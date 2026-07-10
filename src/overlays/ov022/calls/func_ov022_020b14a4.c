extern void func_ov022_020b11e8(unsigned char *a, char *b, int c, int d);
extern int data_ov022_020b2eb8;

unsigned char *func_ov022_020b14a4(char *param_1, int param_2, int param_3, int param_4) {
    unsigned char *r = 0;
    unsigned char *p =
        (unsigned char *)(*(int *)&data_ov022_020b2eb8 + 0x10 + param_2 * 0xa8 + param_3 * 0x38);
    unsigned char b = p[3];
    if (b == 0 || b == 3) {
        r = p;
    }
    if (r[3] == 3) {
        r[0] = 0;
        r[3] = 0;
    }
    if (r != 0) {
        func_ov022_020b11e8(r, param_1, param_4, param_4);
    }
    return r;
}
