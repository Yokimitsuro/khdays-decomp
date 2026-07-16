/* NONMATCHING: semantics verified — everything up to the boot-selector test matches the ROM
 * byte-for-byte. Two divergences remain, both the known "our compiler is smarter" class:
 *   1. the ROM parks the constant 0x1c in the literal pool and reuses it from a register
 *      (`ldr r4,=0x1c; ... mov r1,r4`); mwcc emits the immediate `mov r1,#0x1c` (0x1c fits in
 *      8 bits), dropping the pool entry.
 *   2. the ROM rematerialises `&data_0204c240` at each use (`ldr r2,=..` then `ldr r0,=..`);
 *      mwcc caches the address in a callee-saved reg and reuses it — the pervasive ctx-CSE tie
 *      (see references/deferred-ties.md).
 * Net: 260B vs 272B. Neither is steerable from C.
 *
 * func_ov000_0204ee24 -- ov000 boot entry.
 * Applies the default display config, resets the mode block and the sound/scene state, then reads
 * the boot selector (only when a boot request is pending at heap+0x4c40). Selector 0x191 is the
 * normal path: it clears the boot flags at data_0204c240 and, only if all three ov028 anti-tamper
 * checks pass (0208b490 / 0208b120 / 0208b2e0), stamps 0x2710 and hands off to
 * func_ov000_0204edcc. Any other selector is reported via func_02020a78(5, sel).
 * Always returns -2. */
extern int  NNSi_FndGetCurrentRootHeap(void);
extern void func_02031600(int *cfg);
extern void func_02031618(unsigned short *mode, int arg);
extern void func_020305d8(void);
extern void func_ov000_020588ec(int a, int b);
extern int  func_020235d0(int a, int b);
extern void func_0201e470(int a, int b);
extern int  func_ov028_0208b490(int a);
extern int  func_ov028_0208b120(int a);
extern int  func_ov028_0208b2e0(int a);
extern void func_ov000_0204edcc(void);
extern void func_0201e4a8(int a, int b);
extern void func_02020a78(int a, int b);
extern int  data_0204c240;

int func_ov000_0204ee24(void) {
    int cfg[4];
    unsigned short mode[4];
    int heap = NNSi_FndGetCurrentRootHeap();
    int sel = 0;

    cfg[0] = 1;
    cfg[1] = 1;
    func_02031600(cfg);

    mode[0] = 1;
    mode[1] = 0;
    mode[2] = 0;
    mode[3] = 0;
    func_02031618(mode, 0);

    func_020305d8();
    func_ov000_020588ec(0, 0);

    if (*(int *)(heap + 0x4c40) != 0) {
        sel = func_020235d0(0, 9);
    }

    if (sel == 0x191) {
        *(unsigned short *)((int)&data_0204c240 + 4) = 0;
        *(unsigned char *)((int)&data_0204c240 + 1) = 0;
        func_0201e470(0, 0x1c);
        if (func_ov028_0208b490(0) != 0 && func_ov028_0208b120(0) != 0 &&
            func_ov028_0208b2e0(0) != 0) {
            *(short *)((int)&data_0204c240 + 2) = 0x2710;
            func_ov000_0204edcc();
        }
        func_0201e4a8(0, 0x1c);
    } else {
        func_02020a78(5, sel);
    }
    return -2;
}
