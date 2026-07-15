/* NONMATCHING: semantics correct, param register-allocation tie. The ROM keeps
 * rec_out in r4 and index in r5; mwcc 3.0/139 swaps them (rec_out->r5, index->r4).
 * Params are in fixed order so the callee-saved assignment isn't C-steerable; a
 * cached count local doesn't change it. (Likely the same tie for the sibling per-db
 * decoders FUN_02034730 .. FUN_02034ca0.)
 *
 * MsgDb decoder for db 0x1c: bounds-check index against the db-0x1c entry's count
 * (table + 0x1c*0x14 + 0xc), alloc a 0x10 record (kind 0x1c), and copy the
 * index'th int from the entry's data array (entry[8]) into rec+0xc. */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;
int func_0203498c(int *rec_out, unsigned int index, int keep) {
    int base;
    if (func_020342b4(0x1c) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index < *(unsigned short *)(data_0204c238 + 0x23c)) {
        base = *(int *)(data_0204c238 + 0x238);
        if (func_02034428(rec_out, 0x10, 0x1c, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        *(int *)(*rec_out + 0xc) = *(int *)(base + index * 4);
        return 1;
    }
    return 0;
}
