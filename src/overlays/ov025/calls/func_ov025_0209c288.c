extern int func_ov025_02084c84();

void func_ov025_0209c288(int arg0) {
    int x = func_ov025_02084c84();
    *(int *)arg0 = x;
    *(int *)(arg0 + 0x20) = x;
}
