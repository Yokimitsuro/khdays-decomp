/*
 * NONMATCHING (vec3-copy base-order tie, size-exact byte-diff @0x28). The two
 * guards (DAT flag + bit4 bitfield), the halfword bias `(u16)(h-0x8000)+0x8000`,
 * the |= 0x20, the 2-arg leftover func_02016c90 call, and the args all match.
 * The 3-word `*(vec3)(p+0x878)=*(vec3)(p+0x48c)` copy computes the src base into
 * r0 first in the orig, mwcc computes the dst base first (r0/r1 swap on the ldm).
 *
 * RULED OUT (2026-07-17) -- all leave the diff at 0x28 (which base gets r0: ROM src, mwcc dst):
 *   src pointer local only | dst pointer local only | src-then-dst locals | dst-then-src locals
 *   | copy-through-a-struct-temp (`vec3 tmp=*src; *dst=tmp;`) -- mwcc folds it to the same insns.
 * Re-confirmed 2026-07-17 (2nd pass): the temp spelling compiles BYTE-IDENTICAL. mwcc always
 * computes the lhs (dst) address into r0 first; no source form reorders the two `add rN,r4,#imm`.
 * ARITY IS CLEAN: func_02016ae8 really does take 4 here (the ROM sets r0-r3; the tree's 50
 * three-arg call sites are a different pattern, so audit_arity.py flags this as a FALSE POSITIVE).
 * Same class as ov212_020d1bfc -- a src/dst scratch swap in a 3-word struct copy, where every
 * pointer-local spelling is byte-identical. If one of the two cracks, try the other.
 */
extern void func_02016ae8(int a, int b, int c, int d);
extern void func_0202aa9c(unsigned short *a);
extern void func_02016c90(int a, int b);
extern unsigned char data_0204c240;

struct vec3_0209d3a0 {
    int a;
    int b;
    int c;
};

struct bits_0209d3a0 {
    unsigned char lo4 : 4;
    unsigned char b4 : 1;
    unsigned char hi3 : 3;
};

void func_ov022_0209d3a0(int param_1) {
    int iVar2;
    if ((data_0204c240 & 4) == 0) {
        return;
    }
    if (((struct bits_0209d3a0 *)(param_1 + 0x694))->b4 == 0) {
        return;
    }
    *(struct vec3_0209d3a0 *)(param_1 + 0x878) = *(struct vec3_0209d3a0 *)(param_1 + 0x48c);
    iVar2 = param_1 + 0x700;
    *(unsigned short *)(param_1 + 0x850) =
        (unsigned short)(*(unsigned short *)(*(int *)(param_1 + 0x20) + 0x80) - 0x8000) + 0x8000;
    *(unsigned short *)(param_1 + 0x7d4) = *(unsigned short *)(param_1 + 0x7d4) | 0x20;
    func_02016ae8(*(int *)(param_1 + 0x84c), 1, 0, iVar2);
    func_0202aa9c((unsigned short *)(param_1 + 0x7d4));
    func_02016c90(*(int *)(param_1 + 0x84c), 3);
}
