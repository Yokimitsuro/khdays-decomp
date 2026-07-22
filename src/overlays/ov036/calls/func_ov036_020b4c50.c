/* Push this enemy's animation argument into its three 0x30-byte part records, then run
 * the follow-up pass in func_ov036_020b4c94. One of four byte-identical siblings
 * (ov036/ov055/ov075/ov092) differing only in the overlay and the follow-up target.
 *
 * The part-array base must be left INSIDE the loop for mwcc to hoist. Hoisted code is
 * appended to the END of the preheader, which is where the original has it -- computing
 * it into a local first emits it ahead of the counter init instead, and the two movs
 * come out swapped. The matched sibling func_ov036_020b4c94 hides this because it has
 * no second parameter and therefore nothing to schedule against. */
extern void func_ov022_0209145c(int part, int a);
extern void func_ov036_020b4c94(int this_);

void func_ov036_020b4c50(int this_, int a) {
    int i, off;
    for (i = 0, off = 0; i < 3; i++, off += 0x30) {
        func_ov022_0209145c(((int *)(this_ + 0x2000))[0x191] + off, a);
    }
    func_ov036_020b4c94(this_);
}
