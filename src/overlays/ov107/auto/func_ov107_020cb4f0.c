/* func_ov107_020cb4f0 -- run the task's step function if it is armed (bit 0 of the 16-bit flags
 * field at +0xc) and has one; returns whatever the step returns, or 0.
 *
 * The step takes the caller's second argument as well, and that is why the flags temp lands in r2
 * rather than r1: `arg` arrives in r1 and stays there all the way into the indirect call, so no
 * instruction is emitted for it and the call site looks like it passes one argument. Declared with
 * one parameter the function is one register off and nothing else. */
struct Ov107Flags { unsigned int lo : 16, hi : 16; };

int func_ov107_020cb4f0(int obj, int arg) {
    int (*cb)(int, int);
    if ((((struct Ov107Flags *)(obj + 0xc))->lo & 1) != 0) {
        cb = *(int (**)(int, int))(obj + 4);
        if (cb != 0) {
            return cb(obj, arg);
        }
    }
    return 0;
}
