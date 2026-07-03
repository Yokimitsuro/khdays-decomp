struct s5 { int a, b, c, d, e; };
extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov030_020b3e9c(int a);
extern int data_ov030_020b59ac[];
extern int data_ov030_020b59c0[];
extern int data_ov030_020b59d4[];
extern struct s5 data_ov030_020b58c4;
void func_ov030_020b4b9c(int p1, int state) {
    struct s5 buf;
    *(int *)(state + 0xdb4) = p1;
    *(int *)(state + 0xc) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x230) = 0;
    func_0202a634(state + 0x18, data_ov030_020b59ac, 1, *(unsigned char *)(p1 + 9) + 7);
    if (*(int *)(p1 + 0xc) == 0)
        func_0202a634(state + 0x128, data_ov030_020b59c0, 1, *(unsigned char *)(p1 + 9) + 7);
    else
        func_0202a634(state + 0x128, data_ov030_020b59d4, 1, *(unsigned char *)(p1 + 9) + 7);
    buf = data_ov030_020b58c4;
    buf.b = 4;
    func_ov022_02092384(p1 + 0x2648, *(unsigned char *)(p1 + 9), 5, &buf);
    func_ov030_020b3e9c(state);
}
