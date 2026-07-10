/*
 * [nonmatching: register-allocation: the loop (i/e/off/param_1/arg3 + i+0xd temp) needs 2 extra callee-saved regs vs the original 5 (+8B)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
extern void func_ov022_0208b374(int arg0, int arg1, int arg2, int arg3);
extern void func_ov022_02090070(int arg0);

void func_ov022_0208e7a0(int arg0, int arg1, int arg2, int arg3) {
    int e = *(int *)(arg0 + *(int *)(arg0 + 0xc) * 4 + 0x18);
    int i = 0;
    if ((int)*(unsigned char *)(e + 1) > 0) {
        int off = 0;
        do {
            func_ov022_0208b374(*(int *)(e + 0x168) + off, 1, i + 0xd, arg3);
            i = i + 1;
            off = off + 0x150;
        } while (i < *(unsigned char *)(e + 1));
    }
    if (*(int *)(e + 0x170) != 0) func_ov022_02090070(arg0);
}
