extern int func_02023930(void *cls, void *buf);
extern void func_ov022_020895a4(int arg0, int arg1);
extern int data_ov022_020b2930;

void func_ov022_02092384(int arg0, int arg1, int arg2, unsigned int *arg3) {
    struct { unsigned int w0; unsigned int w1; unsigned int w2; unsigned int w3; int w4; } buf;
    int flag;
    buf.w0 = arg3[0];
    buf.w1 = arg3[1];
    buf.w2 = 0;
    buf.w3 = 0;
    if (arg2 == 0 || arg2 == 5) buf.w4 = arg1 + 7;
    else buf.w4 = 5;
    *(int *)(arg0 + arg2 * 4) = func_02023930(&data_ov022_020b2930, &buf);
    if (arg2 == 0 || arg2 == 2) flag = 0x200;
    else flag = 0x500;
    func_ov022_020895a4(*(int *)(arg0 + arg2 * 4), flag);
}
