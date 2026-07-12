/* Run func_ov009_02051f68, then if the +0x2c pending bit is set run func_ov009_02052108. */
extern void func_ov009_02051f68(int self);
extern void func_ov009_02052108(int self);
struct pend { unsigned char b0 : 1; };
void func_ov009_020522a8(int param_1) {
    func_ov009_02051f68(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_ov009_02052108(param_1);
}
