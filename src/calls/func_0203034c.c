/*
 * Draw_ScaledValue - draw a value through func_02014174 using a cell width chosen by a flag.
 *
 * Picks the cell width from self[0x38] (0x40 wide when set, 0x20 narrow otherwise), divides
 * the value self[0x10] by that width via the 64-bit divide func_02020400, and draws with
 * func_02014174 at (self[4], self[8]) passing the quotient. A negative line-height argument
 * (param_5) defaults to 0xf.
 *
 * param_5 is copied to a local so mwcc keeps it in a register (r4) instead of spilling the
 * modified parameter; the quotient is passed to the draw's u16 slot unmasked (no extra
 * lsl/lsr zero-extend).
 */

extern unsigned long long func_02020400(unsigned int value, unsigned int divisor);
extern void func_02014174(unsigned int a, int b, int c, int d, int e, int f, unsigned int g, int h);

void func_0203034c(int self, unsigned int param_2, int param_3, int param_4, int param_5)
{
    unsigned int width;
    unsigned int q;
    int e = param_5;

    if (e < 0)
        e = 0xf;
    width = *(int *)(self + 0x38) != 0 ? 0x40 : 0x20;
    q = (unsigned int)func_02020400(*(unsigned int *)(self + 0x10), width);
    func_02014174(param_2, *(int *)(self + 4), *(int *)(self + 8), param_4, param_3, 0x40, q, e);
}
