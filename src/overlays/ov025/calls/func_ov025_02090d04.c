extern int func_ov025_02090580();
extern void func_ov025_02090b54();

void func_ov025_02090d04(int arg0, int arg1, char arg2) {
    int base = arg0 + 0x1bf0;
    int t = *(unsigned char *)(base + arg1);
    *(unsigned char *)(base + arg1) = t + arg2;
    int *p = (int *)func_ov025_02090580(arg0, 0, arg1);
    if (p == 0) return;
    *(unsigned char *)((int)p + 5) = *(unsigned char *)(base + arg1);
    if (*(int *)(arg0 + 8) != 0) return;
    func_ov025_02090b54(arg0, *(int *)(*p + 0x14));
}
