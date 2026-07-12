/* Run the three-step sequence: func_ov005_0204d364(param_1), func_ov005_0204d234(param_1, 0), func_ov005_0204d408(param_1). */
extern void func_ov005_0204d364(int arg);
extern void func_ov005_0204d234(int a, int b);
extern void func_ov005_0204d408(int arg);
void func_ov005_0204d4e4(int param_1) {
    func_ov005_0204d364(param_1);
    func_ov005_0204d234(param_1, 0);
    func_ov005_0204d408(param_1);
}
