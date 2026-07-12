/* Two-step teardown: func_ov185_020cfc30(param_1) then func_ov107_020c7da4(param_1). */
extern void func_ov185_020cfc30(int arg);
extern void func_ov107_020c7da4(int arg);
void func_ov185_020cfcc0(int param_1) {
    func_ov185_020cfc30(param_1);
    func_ov107_020c7da4(param_1);
}
