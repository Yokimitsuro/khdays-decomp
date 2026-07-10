extern int func_01fffe14(void);
extern int func_01fffde0(int a);
extern int func_ov002_02076c24(int a, int b);
extern void func_02035fb0(int a, int b, int c, int d, int e);
extern void func_02035ffc(int a);

void func_ov022_02086098(int arg0, int arg1) {
    int kind = *(unsigned char *)(func_01fffde0(func_01fffe14()) + 9);
    int sel = 0;
    if (func_ov002_02076c24(arg1, kind) == 0) sel = 1;
    if (*(int *)(arg0 + 0x128) == arg1) {
        *(int *)(arg0 + 0x120) = sel * 0x30 + (arg0 + 0xc0);
        return;
    }
    *(int *)(arg0 + 0x128) = arg1;
    *(int *)(arg0 + 0x124) = 1;
    *(int *)(arg0 + 0x120) = sel * 0x30 + (arg0 + 0xc0);
    func_02035fb0(arg0 + 0x12c, 2, 0x2d000, 0, 400);
    func_02035ffc(arg0 + 0x12c);
}
