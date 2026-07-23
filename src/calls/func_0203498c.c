/* func_0203498c -- MsgDb decoder for database 0x1c: bounds-check the index, allocate a
 * 0x10-byte record of kind 0x1c and store the table entry into it at +0xc.
 * The table is the pointer/count pair at data_0204c238 + 0x238/+0x23c.
 *
 * Two shapes are load-bearing:
 *  - the byte offset `index * 4` is computed BEFORE the allocation call. The ROM's
 *    `lsls r5, r5, #2` sits above the `bl`, and computing the index at the point of use
 *    schedules it after.
 *  - the success path is reached by a goto, so the local `return 0` stays inline and the
 *    store block goes out of line -- that is the ROM's `bne ->ok ; movs r0,#0 ; pop`
 *    layout. Written as a plain if/else mwcc inlines the success block instead. */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;

int func_0203498c(int *rec_out, unsigned int index, int keep) {
    int base;
    int off;

    if (func_020342b4(0x1c) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index < *(unsigned short *)(data_0204c238 + 0x23c)) {
        base = *(int *)(data_0204c238 + 0x238);
        off = index * 4;
        if (func_02034428(rec_out, 0x10, 0x1c, keep) != 0 && *rec_out != 0) goto ok;
        return 0;
    ok:
        *(int *)(*rec_out + 0xc) = *(int *)(base + off);
        return 1;
    }
    return 0;
}
