/* If func_02028724 accepts the sub-object at +0xc, raises bits 0 and 6 of the flag byte
 * at +8.  The result of the call is returned as well: the ROM keeps it in r0 across the
 * predicated read-modify-write, which is only possible if r0 is still live -- written as
 * a void function mwcc reuses r0 for the byte instead of r1. */
extern int func_02028724(unsigned char *p);

int func_0202c594(unsigned char *o) {
    int r = func_02028724(o + 0xc);
    if (r != 0) {
        o[8] |= 0x41;
    }
    return r;
}
