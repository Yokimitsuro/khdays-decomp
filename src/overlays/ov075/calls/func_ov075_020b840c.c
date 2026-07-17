/*
 * Apply a mode change to the actor (x4: ov036/055/075/092).
 *
 * Entering 0x2e re-inits (020b3928). Any actual mode change then rebinds the actor's animation
 * (020b4b68) -- +0x6bc caches the previous mode. 020a384c hands the mode down, and the UI band
 * gets it either translated (020519b0 -> 02052024, at/above 0x2e) or straight (020521a4, below,
 * with the loop flag set when the anim state at +0x2bb2 is 2).
 *
 * ★ NEW CRACK -- a DEAD COMPARE CHAIN is a switch whose cases have EMPTY bodies. The ROM opens:
 *      cmp r5, #0x2e ; beq <body> ; cmp r5, #0x2f ; cmpne r5, #0x30 ; b <next>
 * Those last two compares set flags nobody reads, and an `if` cannot produce them. They are
 * cases 0x2f and 0x30 of a switch, written with nothing in them but a `break`: mwcc emits the
 * compare chain, then finds the case body IS the fall-through and folds the `beq` into the
 * unconditional `b`, stranding the compares. Ghidra renders the whole head as a plain
 * `if (mode == 0x2e && ...)` and silently drops them, so the disassembly is the only place the
 * two empty cases are visible at all.
 *
 * The rest is the ov034/ov046 template: 020521a4 takes FOUR args; the loop flag is a zero-init
 * plus one conditional set; 020519b0 runs UNCONDITIONALLY before the branch even though only the
 * >= 0x2e arm uses its result, which is why the flag lives in a callee-saved register across it.
 */
extern int data_ov075_020b9e20;
extern void WM_EndKeySharing_0x020b8808(int self);
extern void func_ov075_020b9a48(int self);
extern void func_ov022_020a384c(int self, int mode);
extern int func_ov002_020519b0(int a, int b, int c);
extern void func_ov002_02052024(void *a, int b, int c, int d, int e);
extern void func_ov002_020521a4(void *a, int b, int c, int d);

void func_ov075_020b840c(int self, int mode) {
    int base = data_ov075_020b9e20;
    int flag;
    int ret;

    switch (mode) {
    case 0x2e:
        if (*(int *)(self + 0x6bc) != mode) { WM_EndKeySharing_0x020b8808(self); }
        break;
    case 0x2f:
    case 0x30:
        break;
    }
    if (*(int *)(self + 0x6bc) != mode) { func_ov075_020b9a48(self); }
    func_ov022_020a384c(self, mode);
    flag = 0;
    if (*(signed char *)(self + 0x2bb2) == 2) { flag = 1; }
    ret = func_ov002_020519b0(mode, *(int *)(self + 0x6bc), *(int *)(self + 0xc));
    if (mode >= 0x2e) {
        func_ov002_02052024((void *)(self + 0xda8), base + 0x2c2c, mode, 2, ret);
        return;
    }
    func_ov002_020521a4((void *)(self + 0xda8), base + 0x2c2c, mode, flag);
}
