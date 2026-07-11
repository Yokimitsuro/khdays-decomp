/* NONMATCHING — pure register-coloring permutation (80/80 bytes, byte-structurally
 * identical: same opcodes, same offsets, same control flow — only three register
 * numbers are swapped).
 *
 * Append one entry to a bounded table embedded in the object at param_1. A header
 * sits at +0x4000: count at +0x630, capacity at +0x62c (word indices 0x18c/0x18b).
 * Each slot is 8 bytes: a u32 payload at +0x4638 and a u16 tag at +0x463c.
 * Returns 1 if the entry was stored, 0 if the table was full.
 *
 * The base pointer (param_1+0x4000), the loaded count, and the returned flag all
 * get valid registers, but mwcc colors base->ip / count->r3 while the original
 * colors base->r2 / count->ip. There are no calls, so the choice is arbitrary and
 * unsteerable. Tried: hdr-pointer indexing (this form), direct param_1+off derefs
 * (re-fragments the base into two adds, +8B), and declaration reordering — all keep
 * the byte-identical stream with the same reg permutation. The raw blob keeps the
 * build byte-exact; this documents the equivalent C.
 */
int func_02031a74(int param_1, unsigned int *param_2) {
    int *hdr = (int *)(param_1 + 0x4000);
    int count = hdr[0x18c];
    int stored = 0;

    if (count < hdr[0x18b]) {
        int slot = param_1 + count * 8;
        *(unsigned int *)(slot + 0x4638) = *param_2;
        *(unsigned short *)(slot + 0x463c) = *(unsigned short *)((char *)param_2 + 4);
        hdr[0x18c] = hdr[0x18c] + 1;
        stored = 1;
    }
    return stored;
}
