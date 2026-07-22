/* func_0201a284 -- forward the object's kind byte to the command queue, if the object exists.
 * Guards on *obj != 0, then invokes func_02008158 with the unsigned byte field at (*obj)+0x3c,
 * passing this function's own two trailing arguments straight through; returns 1 (or 0 if *obj
 * is null).
 *
 * Parked as a "1-register colouring tie": the ROM loads *obj for the null check into r3 (the
 * register it pushed only for stack alignment) and mwcc into r1. r3 is not a colouring whim --
 * r1 and r2 are LIVE, because they carry this function's second and third arguments through to
 * func_02008158 (declared with one parameter here and defined with three;
 * tools/audit_extern_sig.py names it). Forwarding them costs no instructions at all, since they
 * are already in the right registers, which is exactly why the call site looks like it takes one
 * argument.
 *
 * The other half was already understood and is still needed: the ROM does NOT common up the two
 * reads of *obj, it re-loads. mwcc folds them into one unless the second goes through a volatile
 * lvalue -- so the volatile is deliberate, not decoration. Neither half matches alone: with the
 * arguments but no volatile it is one instruction short; with the volatile but no arguments it
 * lands one register off. */
extern void func_02008158(int kind, int a, int b);

int func_0201a284(void *obj, int a, int b) {
    if (*(char **)obj == 0) {
        return 0;
    }
    func_02008158(*(unsigned char *)(*(char *volatile *)obj + 0x3c), a, b);
    return 1;
}
