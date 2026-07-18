/* NONMATCHING -- 352/352 B, and the ONLY difference is a scheduling swap inside the
 * fourth func_0203b9fc call:
 *     ROM : ldr r0,[r4,#0x384] ; mov r1,#1 ; mov r2,#0 ; mov r3,r1
 *     mwcc: mov r1,#1 ; ldr r0,[r4,#0x384] ; mov r3,r1 ; mov r2,#0
 * Same instructions, same registers, different order. Tried hoisting the shared 1 into a
 * local (`int one = 1; f(x, one, 0, one)`) -- no change.
 *
 * Head of a 5-member family (352 B), so it is worth finishing.
 *
 * SOLVED on the way here -- do NOT rediscover:
 *  - Ghidra's five `DAT_arm9_ov169__020ce32x` are RELOCS TO FUNCTIONS (020ce33c, 020ce358,
 *    WM_EndKeySharing_0x020ce390, 020ce5a8, 020ce39c). This is a vtable install, not data.
 *  - func_0203bfb4 takes TWO arguments, not the three Ghidra shows: at +0xa0 only r0 and r1
 *    are set up, r2 is a leftover. (Fourth time today that Ghidra invented a trailing arg.)
 *  - the 0x5c flag word is NOT cached in a local across the calls. The ROM computes it into
 *    r2, stores it, and lets the `bl` clobber it; caching it costs a callee-saved register
 *    and the whole push list changes.
 *  - the +0x388 pointer is likewise not cached: `str r0` then re-`ldr` it.
 *  - the final `|= 2` is a BYTE FIELD: `struct Byte8 { unsigned int lo : 8, hi : 24; }`.
 *    A plain `*(unsigned int *)... |= 2` is 8 B short, and neither `(u & ~0xff) | ((u & 0xff)
 *    | 2)` nor the full double-shift spelling survives -- mwcc folds both to `and #0xff`.
 *    Only the bitfield keeps the ROM's lsl#24/lsr#24 + and#0xff. */
struct Byte8 { unsigned int lo : 8, hi : 24; };
extern int func_ov107_020c9440();
extern int func_0203b898();
extern void func_0203bfb4();
extern void func_0203b9fc();
extern void func_0203c7ac(int a, int b);
extern int func_01fffca8();
extern int func_ov107_020c319c();
extern void func_ov169_020ce33c(void);
extern void func_ov169_020ce358(void);
extern void WM_EndKeySharing_0x020ce390(void);
extern void func_ov169_020ce5a8(void);
extern void func_ov169_020ce39c(void);

void func_ov169_020ce1dc(int self) {
    int owner = *(int *)(self + 0x38c);
    unsigned short v;

    *(void **)(self + 8) = (void *)func_ov169_020ce33c;
    *(void **)(self + 0xc) = (void *)func_ov169_020ce358;
    *(void **)(self + 0x1c) = (void *)WM_EndKeySharing_0x020ce390;
    *(void **)(self + 0x30) = (void *)func_ov169_020ce5a8;
    *(void **)(self + 0x1d0) = (void *)func_ov169_020ce39c;
    v = *(unsigned short *)(self + 0x60);
    *(unsigned short *)(self + 0x60) =
        (unsigned short)((v & ~0xff00)
                         | (((((unsigned int)v << 0x10) >> 0x18 | 0x4e) << 0x18) >> 0x10));
    *(unsigned short *)(self + 0x1ae) |= 4;
    *(int *)(self + 0x70) = 0x600;
    *(int *)(self + 0x54) = 0;
    *(int *)(self + 0x58) = 0;
    *(unsigned int *)(*(int *)(self + 0x9c) + 0x5c) |= 4;
    *(int *)(self + 0x384) = func_0203b898(func_ov107_020c9440(owner, 3));
    func_0203bfb4(*(int *)(self + 0x9c), *(int *)(self + 0x384));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 2, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 4, 0, 1);
    func_0203b9fc(*(int *)(self + 0x384), 1, 0, 1);
    func_0203c7ac(*(int *)(self + 0x384), 0);
    *(int *)(self + 0x388) = func_01fffca8(self + 0x22c, 0x10, 100);
    **(int **)(self + 0x388) = func_ov107_020c319c(self + 100);
    ((struct Byte8 *)(*(int *)(self + 0x388) + 8))->lo |= 2;
}
