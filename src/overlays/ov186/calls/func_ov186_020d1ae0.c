/* Two-step teardown: func_ov186_020d1a50(param_1) then func_ov107_020c7da4(param_1). */
extern void func_ov186_020d1a50(int arg);
extern void func_ov107_020c7da4(int arg);
void func_ov186_020d1ae0(int param_1) {
    func_ov186_020d1a50(param_1);
    func_ov107_020c7da4(param_1);
}
