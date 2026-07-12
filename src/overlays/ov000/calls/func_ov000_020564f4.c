/* Run 020561b4, then if the +0x2c pending bit is set run 02056354. */
extern void func_ov000_020561b4(int self);
extern void func_ov000_02056354(int self);
struct pend { unsigned char b0 : 1; };
void func_ov000_020564f4(int param_1) {
    func_ov000_020561b4(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_ov000_02056354(param_1);
}
