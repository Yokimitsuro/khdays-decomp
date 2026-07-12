/* Notify func_ov002_0206d31c, request mode 2 via func_02023c30, return 1. */
extern void func_ov002_0206d31c(int arg);
extern void func_02023c30(int arg);
int func_ov023_0208708c(int param_1) {
    func_ov002_0206d31c(param_1);
    func_02023c30(2);
    return 1;
}
