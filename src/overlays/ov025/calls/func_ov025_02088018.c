/* Run the func_ov025_020883a0 sweep; if the +0x4a7c bit 2 is set, notify 02032428 and clear it. */
extern void func_ov025_020883a0(int);
extern void func_02032428(int);
struct clr_bf { unsigned int b0:1, b1:1, b2:1; };
void func_ov025_02088018(int param_1) {
    func_ov025_020883a0(param_1);
    if (((struct clr_bf *)(param_1 + 0x4a7c))->b2 == 1) {
        func_02032428(param_1);
        *(int *)(param_1 + 0x4a7c) &= ~4;
    }
}
