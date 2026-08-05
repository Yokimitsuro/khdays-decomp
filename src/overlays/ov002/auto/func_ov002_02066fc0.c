/*
 * func_ov002_02066fc0 - relocate a loaded resource header in place (ARM, reloc-free).
 *
 * The header stores several fields as byte offsets relative to its own base; this pass
 * rebases them into absolute pointers by adding `base`:
 *   - base[8]   (pointer to the entry array)      += base
 *   - base[0xc] (a second rebased pointer)         += base
 * then, for each of base[4] entries in the array (stride 0xc), rebases entry[8] += base.
 *
 * The fixups are written as pointer arithmetic (`base + offset`) so mwcc keeps the base
 * pointer as the first add operand (add rD, base, off). `entry` is declared before the
 * loop counter so it claims r2 and pairs with the count in `ldmib r0, {r1, r2}`; the count
 * is re-read every iteration because a stored entry[8] may alias it.
 */
void func_ov002_02066fc0(char *base)
{
    char *entry;
    unsigned i;

    *(char **)(base + 8)   = base + *(int *)(base + 8);
    *(char **)(base + 0xc) = base + *(int *)(base + 0xc);
    entry = *(char **)(base + 8);
    for (i = 0; i < (unsigned)*(int *)(base + 4); i++) {
        *(char **)(entry + 8) = base + *(int *)(entry + 8);
        entry += 0xc;
    }
}
