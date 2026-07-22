/* Runs func_0202e3c4 over the two 0x104-byte sub-blocks that start at +0x6c of the block
 * held at +0x128, then raises the ready word at +0x58c.
 *
 * The function is not void: the ROM leaves the 1 it just stored in r0 across the `pop`,
 * which is only possible if it is also the return value -- as a void function mwcc
 * colours the offset into r0 and the constant into r1 instead.
 * `off` must be initialised FROM `i` (not from a literal 0) so that `i` gets the lower
 * callee-saved register. */
extern void func_0202e3c4(char *p);

int func_02020cc8(char *o) {
    int i;
    int off;
    i = 0;
    off = i;
    do {
        func_0202e3c4(*(char **)(o + 0x128) + 0x6c + off);
        i = i + 1;
        off = off + 0x104;
    } while (i < 2);
    *(int *)(o + 0x58c) = 1;
    return 1;
}
