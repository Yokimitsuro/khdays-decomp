/* Run func_ov026_02082ecc, then if the +0x2c pending bit is set run func_ov026_0208306c. */
extern void func_ov026_02082ecc(int self);
extern void func_ov026_0208306c(int self);
struct pend { unsigned char b0 : 1; };
void func_ov026_0208320c(int param_1) {
    func_ov026_02082ecc(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_ov026_0208306c(param_1);
}
