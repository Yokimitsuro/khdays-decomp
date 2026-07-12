/* Run the three-step sequence: func_ov000_02056748(param_1), func_ov000_02056618(param_1, 0), func_ov000_020567ec(param_1). */
extern void func_ov000_02056748(int arg);
extern void func_ov000_02056618(int a, int b);
extern void func_ov000_020567ec(int arg);
void func_ov000_020568c8(int param_1) {
    func_ov000_02056748(param_1);
    func_ov000_02056618(param_1, 0);
    func_ov000_020567ec(param_1);
}
