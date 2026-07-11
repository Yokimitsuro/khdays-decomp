/* NONMATCHING — register-coloring tie (the entire body matches in opcode, operand
 * shape and control flow; only two registers are swapped, which cascades into two
 * cosmetic instruction-shape differences).
 *
 * In the multi-element scan loop the ROM colors the loop-carried `cur` to r2 and the
 * loop-invariant `node` priority to r3; every mwcc build we have does the reverse
 * (invariant->r2, loop var->r3). That swap in turn changes the tail: the ROM reuses
 * the earlier `cmp next,0` flags as a redundant while-entry `beq` and stores the
 * final link inline as `str node,[prev,#0x10]`, whereas mwcc precomputes `prev+0x10`
 * into the now-free r0 and stores through it. Front (empty / single-element) matches
 * byte-exact; the split point is the very first multi-element load (next reg r2 vs r3).
 *
 * Proven unsteerable: swept all 27 checked-in mwccarm builds x {-O4,p / -O4,s / -O4 /
 * -O3,p} x 3 source structures (do-while, while-guard, inlined head->next) — none
 * reproduces the ROM's coloring. The blob keeps the build byte-exact; this records the
 * intended, readable source.
 *
 * Insert `node` (itself a chain) into the priority-sorted list at *head, ordered by
 * the unsigned priority byte at +0x18 (next link @+0x10). Higher-or-equal priority
 * sorts earlier; node's whole chain is spliced in at the found position. */
void func_02014bb0(int *head, int node) {
    int cur = *head;
    int next;
    if (cur == 0) {
        *head = node;
        return;
    }
    next = *(int *)(cur + 0x10);
    if (next == 0) {
        if (*(unsigned char *)(cur + 0x18) > *(unsigned char *)(node + 0x18)) {
            int t = *(int *)(node + 0x10);
            int e = node;
            while (t != 0) {
                e = *(int *)(e + 0x10);
                t = *(int *)(e + 0x10);
            }
            *(int *)(e + 0x10) = cur;
            *head = node;
            return;
        }
        *(int *)(cur + 0x10) = node;
        return;
    }
    {
        unsigned int np = *(unsigned char *)(node + 0x18);
        int prev = cur;
        cur = next;
        do {
            if (*(unsigned char *)(cur + 0x18) >= np) {
                int t = *(int *)(node + 0x10);
                int e = node;
                while (t != 0) {
                    e = *(int *)(e + 0x10);
                    t = *(int *)(e + 0x10);
                }
                *(int *)(prev + 0x10) = node;
                *(int *)(e + 0x10) = cur;
                return;
            }
            prev = cur;
            cur = *(int *)(cur + 0x10);
        } while (cur != 0);
        *(int *)(prev + 0x10) = node;
    }
}
