/*
 * NON-MATCHING (200/236 bytes; x3 ov005/008/025). Semantics are exact and verified against the
 * disassembly; the ONLY gap is a branch-vs-predicate tie in the two locate() guards. The ROM emits a
 * real branch for each condition (`beq` on hdr==0, `bls` on hdr[1]==0) to a shared out-of-line
 * `mov r,#0` block; mwcc 3.0/patch4 if-converts the `hdr==0 || hdr[1]==0` guard into a predicated
 * chain (`adds; ldrbne; cmpne; moveq r,#0; beq`) no matter how it is written. Tried: zero-first
 * if/else, compute-first if/else, explicit per-condition `goto`, and this inlined helper -- all
 * predicate; -O2,p/-O3,p/-O4,p are identical. The ROM's `bls` (unsigned) on the count check is the
 * tell that retail's compiler branches where patch4 predicates (consistent with the "retail >=140"
 * build hypothesis). See deferred-ties.md "sub-header locate if-conversion".
 *
 * func_ov005_02050d64 -- x3 (ov005/...). Resolve the on-screen XY of a menu-unit resource.
 * Look up the unit's base record (02017088). Locate two sub-headers inside it: a fixed one at
 * base+0x3c (giving the GX command word `cmd`) and a variable one at base + u16@+0x34 (giving a
 * coordinate pair). Each sub-header is found via locate(): NULL / a zero count byte at +1 -> none,
 * else payload at hdr + u16@+6 + 4. Pick the origin from base+0x18 or base+8 depending on whether cmd
 * is a "position" command (bits 26..28 == 0x14000000). If the coord header's flag bit0 is clear, halve
 * both the header X and the base X (<<15 >>16). Emit out[0] = cmd + originXY,
 * out[1] = (unsigned short)(coordX + baseX).
 */
extern int func_02017088(int entry);

static inline unsigned char *locate(unsigned char *hdr) {
    if (hdr == 0 || hdr[1] == 0) {
        return (unsigned char *)0;
    }
    return hdr + *(unsigned short *)(hdr + 6) + 4;
}

void func_ov005_02050d64(int *out, int param2) {
    int base = func_02017088(param2);
    unsigned int *p5;
    unsigned short *p7;
    unsigned int cmd, x, xy, w, flag;

    if (base == 0) {
        p5 = 0;
    } else {
        p5 = (unsigned int *)locate((unsigned char *)(base + 0x3c));
    }

    if (base == 0 || *(unsigned short *)(base + 0x34) == 0) {
        p7 = 0;
    } else {
        p7 = (unsigned short *)locate((unsigned char *)(base + *(unsigned short *)(base + 0x34)));
    }

    cmd = *p5;
    x = (unsigned short)*(unsigned int *)(base + 0x2c);
    if ((cmd & 0x1c000000) == 0x14000000) {
        xy = *(unsigned int *)(base + 0x18);
    } else {
        xy = *(unsigned int *)(base + 8);
    }
    xy = (unsigned short)xy;

    flag = p7[1];
    w = p7[0];
    if ((flag & 1) == 0) {
        w = (w << 15) >> 16;
        x = (x << 15) >> 16;
    }

    out[0] = cmd + xy;
    out[1] = (unsigned short)(w + x);
}
