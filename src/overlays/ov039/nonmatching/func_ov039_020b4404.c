/* EQUIVALENT BUT NOT BYTE-EXACT -- 7 bytes, 2026-07-18.
 *
 * SAME residue as src/overlays/ov047/nonmatching/func_ov047_020b3b40.c -- read that note,
 * it is the canonical one. Pure r7 <-> sb swap: the ROM puts `p` in sb and the `row + off`
 * temp in r7; mwcc does the opposite. Every other register (r4=base, r5=obj, r6=i, r8=off)
 * is already identical.
 *
 * NEW EVIDENCE from this file (2026-07-18): the shape occurs in FOUR independent families
 * with FOUR different loop counts -- ov035 (2), ov039 (6), ov047, ov049 (10) -- and the same
 * C template lands on exactly 7 bytes in all four. So the swap is NOT allocator luck on one
 * function; it is a stable decision, and cracking it would rescue ~16 functions at once.
 *
 * Additionally ruled out here (beyond the ~65 forms listed in the ov047 note):
 *   no temp, address inlined in the store ..................... 31  (much worse)
 *   `int *t` + `t[0x4c] = p` .................................. 7
 *   temp holds only the field, `+ off` folded into the store ... 7
 *   `p` typed `char *`, cast at both uses ..................... 7
 *   store moved before `i = i + 1` ............................ 7
 *   `p += 0x24` before `off += 0x1c8` ......................... 11
 *   temp declared at top, `p` declared after it ............... 13
 *
 * Watch the pool split: these two build `p` with TWO adds (#0x1d4 / #0x304, then #0x2c00),
 * so the C constant is the SUM (0x2dd4 / 0x2f04). Writing only the first add is 4 bytes short
 * and looks like a missing instruction -- it is not. */

extern void WM_EndKeySharing_0x020b15a4(int a, int b);
extern int data_ov039_020b5600;

void func_ov039_020b4404(int self) {
    int i = 0;
    int p = *(int *)&data_ov039_020b5600 + 0x2f04;
    char *base = (char *)self + 0x2000;
    int obj = *(int *)(base + 0x644);
    int off = 0;

    do {
        int t = *(int *)(obj + 0xc) + off;
        WM_EndKeySharing_0x020b15a4(*(int *)(base + 0x63c), p);
        i = i + 1;
        *(int *)(t + 0x130) = p;
        off = off + 0x1c8;
        p = p + 0x24;
    } while (i < 6);
}
