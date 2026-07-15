/* NONMATCHING: semantics correct, strength-reduction/addressing codegen tie.
 * The ROM recomputes the slot address in-loop as `add r1, param_3, i, lsl#3;
 * ldr [r1, #0x34]` (keeps param_3 as base, 0x34 as the ldr immediate, i as a live
 * counter). mwcc 3.0/139 either strength-reduces `*(int*)(param_3 + i*8 + 0x34)`
 * to a walking pointer (+8B) or, for the array-subscript form
 * `((int*)(param_3+0x34))[i*2]` / `((s8*)(param_3+0x34))[i].slot`, hoists
 * `param_3+0x34` into a 7th callee-saved reg (forcing an explicit stack frame,
 * +4B). None reproduce the ROM's in-loop recompute (the SR decision is one of the
 * unsteerable cases flagged in codegen-cracks "Loops"). Whole family
 * (ov000_020570d8 + byte-identical twins) ties identically.
 *
 * For each of up to 4 slots (stride 8) at param_3+0x34, stop at the first null;
 * otherwise dispatch func_ov000_02056bac(ctx, slot, param_2->f20, param_2->f22, 1).
 * Then run the finalizer func_ov000_02056f90(param_2, param_3). */
extern void func_ov000_02056bac(int ctx, int slot, int a, int b, int flag);
extern void func_ov000_02056f90(int param_2, int param_3);
void func_ov000_020570d8(int ctx, int param_2, int param_3) {
    int i;
    int a = *(unsigned short *)(param_2 + 0x20);
    for (i = 0; i < 4; i++) {
        int slot = *(int *)(param_3 + i * 8 + 0x34);
        if (slot == 0) break;
        func_ov000_02056bac(ctx, slot, a, *(unsigned short *)(param_2 + 0x22), 1);
    }
    func_ov000_02056f90(param_2, param_3);
}
