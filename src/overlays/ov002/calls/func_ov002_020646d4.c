/*
 * Subsystem-state guard stub, reached through the tail-call veneer at 02063574.
 *
 * It loads the ov002 subsystem state pointer and returns whichever way the test goes: the
 * retail build has no body left after the guard. The read is not dead code to the compiler
 * because the early return keeps it, which is exactly why the ROM still contains the load
 * and the compare - an empty if() over the same test folds to a bare `bx lr` at 2 bytes.
 *
 * The value stays in r0 on return, so the veneer's caller sees the state pointer; that is a
 * side effect of the guard, not a declared return value, and the function is void.
 */

extern int data_ov002_0207f634;

void func_ov002_020646d4(void) {
    if (data_ov002_0207f634 == 0) {
        return;
    }
}
