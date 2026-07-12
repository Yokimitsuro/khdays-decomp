/* Run func_ov025_02088e4c, then if the +0x2c pending bit is set run func_ov025_02088fec. */
extern void func_ov025_02088e4c(int self);
extern void func_ov025_02088fec(int self);
struct pend { unsigned char b0 : 1; };
void func_ov025_0208918c(int param_1) {
    func_ov025_02088e4c(param_1);
    if (((struct pend *)(param_1 + 0x2c))->b0)
        func_ov025_02088fec(param_1);
}
