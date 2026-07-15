/* NONMATCHING: semantics correct, param register-allocation tie (r4<->r5 for
 * rec_out/index). The first call is func_020342b4(0x1c) with a CONSTANT db, so no
 * param constrains the callee-saved assignment (unlike MsgDb_DecodeGenericRecord,
 * which passes param_2 to IsLoaded and matches). mwcc 3.0/139 gives rec_out->r5,
 * index->r4; the ROM gives rec_out->r4, index->r5. Not C-steerable (param order is
 * fixed; local copies coalesce). The sibling per-db decoders that call IsLoaded with
 * a constant db likely tie the same way.
 *
 * MsgDb decoder for db 0x1c: bounds-check index against the db-0x1c entry's count
 * (table + 0x1c*0x14 + 0xc), alloc a 0x10 record (kind 0x1c), and copy the index'th
 * int from the entry's data array (entry[8]) into rec+0xc. */
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
        if (func_02034428(rec_out, 0x10, 0x1c, keep) != 0 && *rec_out != 0) {
            *(int *)(*rec_out + 0xc) = *(int *)(base + index * 4);
            return 1;
        }
        return 0;
    }
    return 0;
}
