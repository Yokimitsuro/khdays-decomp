struct s5 { int a, b, c, d, e; };
extern void func_0202a634(int a, void *b, int c, int d);
extern void func_ov022_02092384(int a, int b, int c, void *d);
extern void func_ov044_020b3ad0(int a);
extern int data_ov044_020b55d8[];
extern int data_ov044_020b55ec[];
extern int data_ov044_020b5600[];
extern struct s5 data_ov044_020b54d4;
void func_ov044_020b47d0(int p1, int state) {
    struct s5 buf;
    *(int *)(state + 0xdb4) = p1;
    *(int *)(state + 0xc) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x230) = 0;
    func_0202a634(state + 0x18, data_ov044_020b55d8, 1, *(unsigned char *)(p1 + 9) + 7);
    if (*(int *)(p1 + 0xc) == 0)
        func_0202a634(state + 0x128, data_ov044_020b55ec, 1, *(unsigned char *)(p1 + 9) + 7);
    else
        func_0202a634(state + 0x128, data_ov044_020b5600, 1, *(unsigned char *)(p1 + 9) + 7);
    buf = data_ov044_020b54d4;
    buf.b = 4;
    func_ov022_02092384(p1 + 0x2648, *(unsigned char *)(p1 + 9), 5, &buf);
    func_ov044_020b3ad0(state);
}
