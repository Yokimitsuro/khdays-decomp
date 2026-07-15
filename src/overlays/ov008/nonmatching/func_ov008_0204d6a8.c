/* NONMATCHING: correct; +4B frame-layout tie only. The ROM stores param_4 into the struct's
 * 3rd word via the prologue push {r3,r4,r5,lr} (the r3 push doubles as the store); our mwcc
 * emits push {r4,r5,lr} + a separate str r3,[sp,#8]. No C form reliably forces the arg-reg push. */
/* func_ov008_0204d6a8 -- refresh one save slot's summary widget, ov008.
 * For the given slot index, if a save accessor exists (func_020315c0), builds a 3-word info
 * record { *slot, func_ov008_0204d640(slot), <caller r3> } on the stack and hands it to the
 * widget renderer func_02031618. Does nothing when the slot has no accessor. */
extern int  func_020315c0(int slot);
extern int  func_ov008_0204d640(int slot);
extern void func_02031618(short *info, int slot);

void func_ov008_0204d6a8(int slot, int p2, int p3, int p4) {
    int info[3];
    info[2] = p4;
    if (func_020315c0(slot) != 0) {
        int v = func_ov008_0204d640(slot);
        info[0] = *(int *)func_020315c0(slot);
        info[1] = v;
        func_02031618((short *)info, slot);
    }
}
