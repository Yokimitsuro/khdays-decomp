extern void func_ov022_020b18f8(int arg0, int arg1, char arg2);
void func_ov022_020b19cc(int arg0, int arg1, char arg2) {
    int c = -1;
    if (arg1 >= 0x1b) c = arg1 - 0x1b;
    *(char *)(arg0 + 0xc) = c;
    *(char *)(arg0 + 0xd) = arg2;
    func_ov022_020b18f8(arg0, arg1, arg2);
}
