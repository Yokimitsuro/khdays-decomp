/* Two-step teardown: func_ov187_020d5690(param_1) then func_ov107_020c7da4(param_1). */
extern void func_ov187_020d5690(int arg);
extern void func_ov107_020c7da4(int arg);
void func_ov187_020d5720(int param_1) {
    func_ov187_020d5690(param_1);
    func_ov107_020c7da4(param_1);
}
