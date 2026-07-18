/* NONMATCHING -- 140 vs 152 B. Head of a 6-member family (ov004/005/008 + 3 more).
 *
 * Two independent blockers, both known classes:
 *  1. STRENGTH REDUCTION. The ROM recomputes the entry address from the counter every
 *     iteration (`add r1, r8, r4, lsl #3`); mwcc turns it into a walking pointer
 *     (`add r5, r5, #8`) and burns an extra callee-saved register (fp) on it. Tried the
 *     cached `e` local, the inline byte-offset spelling `*(int *)(c + i*8 + 0x34)`, and
 *     the typed-array form `((struct ent *)(c + 0x34))[i]` -- all three walk.
 *  2. ctx-CSE. The ROM loads the node field TWICE from the same address -- once into r0
 *     for the `== 0` guard and again into r1 as the call argument. mwcc CSEs the two
 *     into one. Same class tiescan.py already filters for.
 *
 * The semantics are believed right (Ghidra + disasm agree): for i == 0 the first scale
 * factor is NOT applied, for i != 0 it is. That asymmetry is real, not a Ghidra artifact.
 *
 * ⚠ Selection lesson for the family vein: this shape (counter-driven loop + repeated
 * field reads) hits two ties at once. Prefer family heads with straight-line control
 * flow; the 12-member ov167 family that matched first-try had no loop at all. */
struct ent { int node; unsigned short sx, sy; };
extern void func_ov004_0204d640(int a, int node, unsigned int sx, unsigned int sy, int e);
extern void func_ov004_0204d91c(int b, int c);

void func_ov004_0204dac4(int a, int b, int c, int d) {
    unsigned short sx = *(unsigned short *)(b + 0x20);
    unsigned short sy = *(unsigned short *)(b + 0x22);
    int i = 0;
    do {
        struct ent *e = &((struct ent *)(c + 0x34))[i];
        if (e->node == 0) {
            break;
        }
        if (i == 0) {
            func_ov004_0204d640(a, e->node, e->sx, sy * e->sy, d);
        } else {
            func_ov004_0204d640(a, e->node, sx * e->sx, sy * e->sy, d);
        }
        i = i + 1;
    } while (i < 4);
    func_ov004_0204d91c(b, c);
}
