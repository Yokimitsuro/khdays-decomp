extern void func_ov025_020ad040();
extern void func_02033b78();

void func_ov025_020ad768(int arg0, int arg1, int arg2, int arg3) {
    unsigned char b;
    if (*(int *)(arg0 + 0x158) != 0) return;
    if (*(int *)(arg0 + 0x180) != 0) return;
    b = *(unsigned char *)(arg0 + 0x17a);
    if (b > 1 && (b = *(unsigned char *)(arg0 + 0x178)) > 1) {
        func_ov025_020ad040(arg0, 1, arg2, arg3);
        func_02033b78(0, 2);
    }
}
