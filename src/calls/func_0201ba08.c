extern int func_02010c2c();
extern int func_0201bb6c();
extern void func_02010c7c();

int func_0201ba08(int arg0) {
    if (func_02010c2c(*(int *)arg0, *(unsigned short *)(arg0 + 0xc)) == 0) return -1;
    if (func_0201bb6c(arg0) != 0) return *(unsigned short *)(arg0 + 0xc) - 1;
    func_02010c7c(*(int *)arg0, 0);
    return -1;
}
