/* Insert `node` into the priority-ordered list at *head.
 *
 * Three things about the second loop are load-bearing and each looks arbitrary alone:
 *  - it is a `while`, not a `do/while`. Its entry test compiles to the `beq` at +0x60 that
 *    can never fire (we only reach +0x60 via the `bne` above it), reusing the flags from
 *    the `next == 0` compare. A do/while has no entry test and loses that instruction.
 *  - it walks `next` itself, not a copy. A fresh variable makes mwcc re-compare instead
 *    of reusing those flags.
 *  - `np` is declared INSIDE the body even though it is loop-invariant. mwcc hoists it to
 *    just after the entry test (+0x64), which is where the ROM has it; declaring it before
 *    the loop schedules the load ahead of the compare instead. */
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
        int prev = cur;
        while (next != 0) {
            unsigned int np = *(unsigned char *)(node + 0x18);
            if (*(unsigned char *)(next + 0x18) >= np) {
                int t = *(int *)(node + 0x10);
                int e = node;
                while (t != 0) {
                    e = *(int *)(e + 0x10);
                    t = *(int *)(e + 0x10);
                }
                *(int *)(prev + 0x10) = node;
                *(int *)(e + 0x10) = next;
                return;
            }
            prev = next;
            next = *(int *)(next + 0x10);
        }
        *(int *)(prev + 0x10) = node;
    }
}
