extern int func_02021980();
extern int func_ov002_02071ba4();

int func_ov002_02074d0c(int arg0, int arg1) {
    int a = func_02021980(arg0, arg1);
    int b = func_02021980(arg0, arg1 + 8);
    func_ov002_02071ba4(a, b);
    return 1;
}
