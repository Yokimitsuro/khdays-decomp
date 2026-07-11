/* NONMATCHING - register-coloring tie in the shared body (the whole function
 * matches in opcode/operand/control-flow; only the tail registers are swapped).
 *
 * After the indexed element lookup, the ROM colors the `mla` result (the element
 * pointer) to r1 (reusing idx's now-dead register), which lets it also carry the
 * merged target node in r1; every mwcc build we have colors that result to r0 and
 * keeps the target in lr instead. From the `mla` onward every instruction differs
 * only in r0/lr vs r1 - no operand or opcode changes. Front (obj resolve, bounds
 * check, index math with base+off+4 addend) is byte-exact.
 *
 * Proven unsteerable: swept all 27 checked-in mwccarm builds x (-O4,p / -O4,s / -O4)
 * x 3 source structures (goto-merge, separate result var, int vs pointer elem) -
 * none reproduces the ROM's coloring. One of a 5-member family (func_020169f8/
 * 02016a70/02016ae8/02016bd8/02016b60) that share this identical middle and differ
 * only in the final bitfield written; all 5 hit the same tie. Blob keeps byte-exact.
 *
 * Resolve a child node from obj (base+slot, where slot=*(obj+8) when obj!=0), index
 * into its element table by `idx` (bounds-checked against the count at +5, entries
 * sized by the halfword at +10, each prefixed by a signed self-offset), then set
 * bitfield [16-20] of that node's flags word (+0xc) to `val`. */
void func_02016bd8(int obj, unsigned int idx, unsigned int val, int slot) {
    int target;
    if (obj != 0 && (slot = *(int *)(obj + 8)) != 0) target = obj + slot;
    else target = 0;
    if (target != 0) {
        int base = target + 4;
        int *elem;
        if (base != 0 && idx < *(unsigned char *)(target + 5)) {
            unsigned int off = *(unsigned short *)(target + 10);
            elem = (int *)(idx * *(unsigned short *)(base + off) + (base + off + 4));
        } else {
            elem = 0;
        }
        if (elem != 0) {
            target = target + *elem;
            goto done;
        }
    }
    target = 0;
done:
    *(unsigned int *)(target + 0xc) = *(unsigned int *)(target + 0xc) & ~0x1f0000U | (val << 16);
}
