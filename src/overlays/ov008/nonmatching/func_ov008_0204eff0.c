/* NONMATCHING: ctx-CSE tie — mwcc caches *(&data_02090f04+4) in a callee-saved reg across the
 * interpolator call (pushes r4 + stack, 76B), the ROM reloads it from the literal pool (72B).
 * Same class as func_ov008_02050970. */
/* func_ov008_0204eff0 -- start the ov008 cursor's scroll interpolator (channel at ctx+0x95d8),
 * from its current value (ctx+0x95d4) to param_1<<12 (Q12) over param_2. */
extern void func_02035fb0(unsigned int *interp, int mode, unsigned int from, unsigned int to, unsigned int dur);
extern void func_02035ffc(unsigned int *interp);
extern int  data_ov008_02090f04[];   /* [1] -> shared screen context */

void func_ov008_0204eff0(int param_1, unsigned int param_2) {
    func_02035fb0((unsigned int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95d8), 0,
                  *(unsigned int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95d4),
                  param_1 << 0xc, param_2);
    func_02035ffc((unsigned int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x95d8));
}
