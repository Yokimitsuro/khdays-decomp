/*
 * Release the resources held by every entry of a node's slot table. Index at obj+0x6bc names the
 * node; bail if it is negative, or if it already equals param_2 and the busy flag (bit 31 of the
 * u64 at obj+0x464) is clear. Fetch the node from obj[index] (table at +0x6c0); for each of its
 * node[1] entries (array at *(node+4)), if the entry's bit0 (entry+4) is set and its handle
 * (entry+8) is non-zero, hand the handle to func_02033e48; then clear the handle and the entry's
 * bit1.
 *
 * Codegen levers that make it byte-exact (all real source facts, not noise):
 *  - the entry fetch is an array subscript `((int*)(*(int*)(node+4)))[i]`, NOT `+ i*4`, so mwcc
 *    indexes with `[base, i, lsl #2]` instead of spending a register on a strength-reduced offset;
 *  - the busy-flag test is a genuine u64 read addressed through `(char*)obj + 0x464`, which keeps
 *    both words on the obj base (`ldr [obj,#0x464]`/`[obj,#0x468]`) instead of a split base;
 *  - the guard is `bit0 != 0 && (handle = entry[8]) != 0` with the handle assigned inside the
 *    condition, so mwcc predicates the short-circuit off the flags rather than materialising a
 *    boolean into a callee-saved register;
 *  - bit0 is `(unsigned)((int)*(unsigned char*)(entry+4) << 0x1f) >> 0x1f`: the `(int)` stops mwcc
 *    folding the extract to `tst`, the `(unsigned)` before the final shift keeps it logical, and
 *    `*(unsigned char*)` keeps the load `ldrb` -- reproducing the ROM's `ldrb; lsl; lsrs`.
 */
extern void func_02033e48(unsigned int a);

void func_ov022_020a46f8(int param_1, int param_2) {
    int iVar2 = *(int *)(param_1 + 0x6bc);
    int iVar3;
    if (iVar2 < 0) return;
    if (iVar2 == param_2 && (*(unsigned long long *)((char *)param_1 + 0x464) & 0x80000000) == 0) return;
    iVar2 = *(int *)(param_1 + iVar2 * 4 + 0x6c0);
    if (iVar2 == 0) return;
    iVar3 = 0;
    if (0 < (int)*(unsigned char *)(iVar2 + 1)) {
        do {
            int iVar4 = ((int *)(*(int *)(iVar2 + 4)))[iVar3];
            unsigned int uVar1 = (unsigned int)((int)*(unsigned char *)(iVar4 + 4) << 0x1f) >> 0x1f;
            if (uVar1 != 0 && (uVar1 = *(unsigned int *)(iVar4 + 8)) != 0) func_02033e48(uVar1);
            *(int *)(iVar4 + 8) = 0;
            iVar3 = iVar3 + 1;
            *(unsigned char *)(iVar4 + 4) &= ~2;
        } while (iVar3 < (int)*(unsigned char *)(iVar2 + 1));
    }
}
