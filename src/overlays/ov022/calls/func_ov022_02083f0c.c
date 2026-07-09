extern int *data_ov022_020b2e60;
extern unsigned char data_0204be04;
int func_ov022_02083f0c(void) {
    int *p = data_ov022_020b2e60;
    if (p == 0) return -1;
    if (data_0204be04 == 0) return p[3];
    return p[6];
}
