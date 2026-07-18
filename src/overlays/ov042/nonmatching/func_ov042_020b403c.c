/* EQUIVALENT BUT NOT BYTE-EXACT -- 7 bytes, 2026-07-18.
 *
 * SAME residue as src/overlays/ov047/nonmatching/func_ov047_020b3b40.c (the canonical note)
 * and the ov035/ov039 parks: the r7 <-> sb swap between `p` and the `row + off` temp.
 *
 * This is the FIFTH family with this shape (ov035, ov039, ov042, ov047, ov049), so the residue
 * now blocks ~20 functions. Loop counts 2, 6, 6, 10, 10 -- all land on exactly 7 bytes with the
 * same template, which is why the ov047 note calls it a stable mwcc decision rather than
 * allocator luck. Do not re-derive it here; ~70 forms are already ruled out over there.
 *
 * Pool split note: `p` is built with two adds (#0x394 then #0x3000), so the C constant is the
 * SUM, 0x3394. Writing only the first add gives "size -4" and looks like a missing instruction. */

extern void WM_EndKeySharing_0x020b15a4(int a, int b);
extern int data_ov042_020b4800;

void func_ov042_020b403c(int self) {
    int i = 0;
    int p = *(int *)&data_ov042_020b4800 + 0x3394;
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
