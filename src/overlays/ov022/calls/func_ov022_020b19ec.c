extern void func_ov022_020b18f8(int *arg0, int arg1, int arg2, int arg3);
int func_ov022_020b19ec(int *arg0, int arg1, int arg2, int arg3) {
    int r = 0;
    int c = r - 1;
    if (arg1 >= 0x1b) c = arg1 - 0x1b;
    *(char *)(arg0 + 3) = c;
    func_ov022_020b18f8(arg0, arg1, c, arg3);
    if (*(unsigned char *)(arg0 + 2) == 3) r = 1;
    return r;
}
