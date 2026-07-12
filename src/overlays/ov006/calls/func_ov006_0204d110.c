/* Run func_ov006_0204cdd0, then if the +0x2c pending bit is set run func_ov006_0204cf70. */
extern void func_ov006_0204cdd0(int self);
extern void func_ov006_0204cf70(int self);
struct pend { unsigned char b0 : 1; };
void func_ov006_0204d110(int param_1) {
    func_ov006_0204cdd0(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_ov006_0204cf70(param_1);
}
