/* Run the three-step sequence: func_ov009_020524fc(param_1), func_ov009_020523cc(param_1, 0), func_ov009_020525a0(param_1). */
extern void func_ov009_020524fc(int arg);
extern void func_ov009_020523cc(int a, int b);
extern void func_ov009_020525a0(int arg);
void func_ov009_020526b8(int param_1) {
    func_ov009_020524fc(param_1);
    func_ov009_020523cc(param_1, 0);
    func_ov009_020525a0(param_1);
}
