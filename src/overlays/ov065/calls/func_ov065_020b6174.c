extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov065_020b627c(int base);
extern int data_ov065_020b7340;
extern int data_ov065_020b7300;
extern int data_ov065_020b7314;

void func_ov065_020b6174(void) {
    int i;
    char *q;
    char *r;
    int j;
    int base = *(int *)&data_ov065_020b7340;
    char *p = (char *)(base + 0x2c80);
    *(int *)(p + 0x110) = 0;
    *(int *)(p + 0x11c) = 0;
    for (i = 0, q = p; i < 6; i++, q += 0x120) {
        *(int *)(q + 0x128) = 0;
    }
    func_0202a634((int)(p + 4), &data_ov065_020b7300, 1, *(unsigned char *)(base + 9) + 7);
    for (j = 0, r = p + 0x12c; j < 6; j++, r += 0x120) {
        func_0202a634((int)r, &data_ov065_020b7314, 1, *(unsigned char *)(base + 9) + 7);
    }
    func_ov065_020b627c(base);
}
