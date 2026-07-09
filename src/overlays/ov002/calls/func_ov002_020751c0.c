extern int func_02021980();
extern int func_ov002_02073d0c();

int func_ov002_020751c0(int arg0, int arg1) {
    int a = func_02021980(arg0, arg1);
    int b = func_02021980(arg0, arg1 + 8);
    func_ov002_02073d0c(a, b);
    return 1;
}
