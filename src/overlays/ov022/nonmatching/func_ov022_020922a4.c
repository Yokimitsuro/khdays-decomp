/*
 * NONMATCHING (mwcc over-folds two constant idioms, -12B):
 *  (1) The bit0 guard is `((byte << 0x1f) >> 0x1f) == 0` (orig: lsl#0x1f then
 *      a separate lsrs#0x1f + predicated return). mwcc folds it to `tst #1`.
 *  (2) The flag set is `uVar3 = (unsigned short)(uVar3 | 1)` (orig: orrle then
 *      lslle#0x10/lsrle#0x10 to truncate to u16). Because uVar3 is provably 0
 *      at that point, mwcc folds it to a bare `movle r4, #1` with no mask.
 * Both idioms survive in the original (a lower opt level / wider dataflow kept
 * uVar3 non-constant), but this toolchain constant-propagates them away. Logic
 * is byte-equivalent.
 *
 * if (byte@0x694 bit0 == 0) return;
 * uVar1 = func_02030788();
 * if (*(u8)(p+2)==uVar1 && (*p & 0x10000)==0 && func_01ff8e94(p+0x48c,arg1)<=0x2000)
 *     flag = 1;
 * func_02033d0c(arg2, arg3, arg1, flag);
 */
extern int func_02030788(void);
extern int func_01ff8e94(int *a, int *b);
extern void func_02033d0c(unsigned int a, unsigned int b, int *c, unsigned int d);

void func_ov022_020922a4(unsigned int *param_1, int *param_2, unsigned int param_3,
                         unsigned int param_4) {
    unsigned short uVar3 = 0;
    if ((((unsigned int)*(unsigned char *)(param_1 + 0x1a5) << 0x1f) >> 0x1f) == 0) {
        return;
    }
    if (*(unsigned char *)(param_1 + 2) == func_02030788() &&
        (*param_1 & 0x10000) == 0 &&
        func_01ff8e94((int *)(param_1 + 0x123), param_2) <= 0x2000) {
        uVar3 = uVar3 | 1;
    }
    func_02033d0c(param_3, param_4, param_2, uVar3);
}
