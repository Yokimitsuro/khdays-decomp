/* NONMATCHING: ctx-CSE tie — the ROM reloads *(&data_02090f04+4) before each of the four uses
 * (84B); mwcc caches it in a callee-saved reg and folds three reloads (72B). Same class as
 * func_ov008_02050970 / 0204eff0. */
/* func_ov008_02050a64 -- set the ov008 active page to param_1: pushes it to the page widget
 * (ctx+0x9500), updates the two control bits at ctx+0xa7c (func_ov008_02054e4c/02054e24), and
 * records it at ctx+0x9600. */
extern void func_ov008_02055c08(int widget, unsigned int page);
extern void func_ov008_02054e4c(int ctx, unsigned int page);
extern void func_ov008_02054e24(int ctx, unsigned int page);
extern int  data_ov008_02090f04[];   /* [1] -> shared screen context */

void func_ov008_02050a64(unsigned int param_1) {
    func_ov008_02055c08(*(int *)((int)data_ov008_02090f04 + 4) + 0x9500, param_1);
    func_ov008_02054e4c(*(int *)((int)data_ov008_02090f04 + 4), param_1);
    func_ov008_02054e24(*(int *)((int)data_ov008_02090f04 + 4), param_1);
    *(unsigned int *)(*(int *)((int)data_ov008_02090f04 + 4) + 0x9600) = param_1;
}
