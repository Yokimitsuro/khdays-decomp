/*
 * func_ov002_0207c67c - dispatch func_01fff774 for each active entry of a 5-slot table (ARM).
 *
 * Walks slots 0..4 of the signed-halfword table at param_1+0xe0; for every slot holding a positive
 * value it calls func_01fff774(param_1, slot, param_2). The slot index is taken as an unsigned short
 * so the halfword access is computed as `base + idx*2 + 0xe0` (idx*2 offset, 0xe0 folded into the
 * ldrsh immediate) rather than hoisting a base+0xe0 pointer, which keeps the register footprint to
 * three callee-saved regs.
 */
extern int *func_01fff774(int a, int b, int c);

void func_ov002_0207c67c(int param_1, int param_2)
{
    int i;
    for (i = 0; i < 5; i++) {
        unsigned short idx = i;
        if (*(short *)(param_1 + idx * 2 + 0xe0) > 0) {
            func_01fff774(param_1, idx, param_2);
        }
    }
}
