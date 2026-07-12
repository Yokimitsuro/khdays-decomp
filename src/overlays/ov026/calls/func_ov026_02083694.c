/* Run the three-step sequence: func_ov026_02083460(param_1), func_ov026_02083330(param_1, 0), func_ov026_02083504(param_1). */
extern void func_ov026_02083460(int arg);
extern void func_ov026_02083330(int a, int b);
extern void func_ov026_02083504(int arg);
void func_ov026_02083694(int param_1) {
    func_ov026_02083460(param_1);
    func_ov026_02083330(param_1, 0);
    func_ov026_02083504(param_1);
}
