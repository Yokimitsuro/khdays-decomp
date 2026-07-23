/* func_ov024_02083368 -- open the up-to-three streams a MobiClip descriptor asks for.
 * The descriptor is three 8-halfword records; a record whose first halfword is 2 is opened
 * with func_02021948 and its handle kept. The three handles (0 for the records that were not
 * opened) are handed to func_ov024_02082c98. Always reports success.
 *
 * The three handles are zeroed with a CHAINED assignment. As three separate statements mwcc
 * picks the FIRST handle for the stack slot and keeps the third in a register; the chain
 * initialises them in the opposite order and swaps that choice, which is what the ROM does
 * (`adds r7, r0, #0` for the first handle, `str` for the third). */
extern int func_02021948(int owner, short *entry);
extern void func_ov024_02082c98(int a, int b, int c);

int func_ov024_02083368(int owner, short *desc) {
    int h0;
    int h1;
    int h2;

    h0 = h1 = h2 = 0;
    if (desc[0] == 2) {
        h0 = func_02021948(owner, desc);
    }
    if (desc[4] == 2) {
        h1 = func_02021948(owner, desc + 4);
    }
    if (desc[8] == 2) {
        h2 = func_02021948(owner, desc + 8);
    }
    func_ov024_02082c98(h0, h1, h2);
    return 1;
}
