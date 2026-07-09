extern int func_02030788();
extern int func_020315c0();

int func_ov025_020b0e3c(int arg0) {
    int p = func_020315c0(func_02030788(arg0));
    return p == 0 ? -1 : *(int *)(p + 4);
}
