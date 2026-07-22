/* Returns entry `b` of the 4-byte {count, value} array at +0x3c of record `a` in the
 * 260-byte-stride table data_0204c678, or NULL when either half is zero.
 *
 * `r` has to be declared BEFORE `e`: that ordering is what makes the result live in a
 * callee-saved register and the table base spill into r4, exactly as the ROM does.
 * The first read is written through `rec + b * 4` rather than through `e` so that it
 * keeps the base+index addressing form. */
extern unsigned char data_0204c678[];

short *func_02035874(int a, int b) {
    unsigned char *rec = data_0204c678 + a * 260 + 0x3c;
    short *r = 0;
    short *e = (short *)(rec + b * 4);
    if (*(unsigned short *)(rec + b * 4) != 0 && e[1] != 0) {
        r = e;
    }
    return r;
}
