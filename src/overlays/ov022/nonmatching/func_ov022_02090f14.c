/* NONMATCHING: register-coloring tie. Structure byte-identical (72B) — the loop
 * counter i and stride offset e land in r4/r5 swapped vs the original (orig
 * mov r4,#0; mov r5,r4). Tried decl reorder and `int e=i`. Iterates the
 * *(arg0+0xc) 0x1c8-stride array (count byte@+0x19) calling func_ov022_02090cac,
 * then func_020236ac. */
extern void func_ov022_02090cac(int arg0);
extern void func_020236ac(int arg0);
void func_ov022_02090f14(int arg0) {
    int i = 0, e = 0;
    for (; i < *(unsigned char *)(arg0 + 0x19); i++, e += 0x1c8)
        func_ov022_02090cac(*(int *)(arg0 + 0xc) + e);
    func_020236ac(*(int *)(arg0 + 0xc));
}
