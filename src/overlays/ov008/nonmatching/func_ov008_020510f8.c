/* NONMATCHING: register-allocation tie — mwcc parks &data_02090f04 in a callee-saved reg (r5,
 * pushes it) for the pre-call access, the ROM uses a caller-saved reg (r1); the differing reg
 * choice shifts the literal-pool placement (76B vs 80B). Same class as the ctx-CSE ties. */
/* func_ov008_020510f8 -- tick down the pending-refresh counter for UI bank param_1.
 * If the counter (ctx+param_1*4+0x96bc) is < 1 do nothing; if it is exactly 1 (last tick) run the
 * refresh func_02034258; then decrement it. */
extern void func_02034258(int bank);
extern int  data_ov008_02090f04[];   /* [1] -> shared screen context */

void func_ov008_020510f8(int param_1) {
    int count = *(int *)(*(int *)((int)data_ov008_02090f04 + 4) + param_1 * 4 + 0x96bc);
    if (count < 1) {
        return;
    }
    if (count == 1) {
        func_02034258(param_1);
    }
    *(int *)(*(int *)((int)data_ov008_02090f04 + 4) + param_1 * 4 + 0x96bc) -= 1;
}
