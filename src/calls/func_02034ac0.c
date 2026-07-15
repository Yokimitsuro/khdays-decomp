/* MsgDb decoder for db 0x1d: bounds-check index (signed) against the db-0x1d entry's
 * count (table + 0x1d*0x14 + 0xc = +0x250), alloc a 0xdc record (kind 0x1d), then
 * store index + elem[0..2] and copy 24 pairs (stride 8) from elem+0xc into rec+0x1c.
 * elem = entry[8] + index*0xcc. *rec_out is re-read per store. */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;
int func_02034ac0(int *rec_out, int index, int keep) {
    int elem;
    int *ep;
    int i, off;
    if (func_020342b4(0x1d) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0 && index < *(unsigned short *)(data_0204c238 + 0x250)) {
        elem = *(int *)(data_0204c238 + 0x24c) + index * 0xcc;
        ep = (int *)(elem + 0xc);
        if (func_02034428(rec_out, 0xdc, 0x1d, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        *(int *)(*rec_out + 0xc) = index;
        *(int *)(*rec_out + 0x10) = *(int *)elem;
        *(int *)(*rec_out + 0x14) = *(int *)(elem + 4);
        *(int *)(*rec_out + 0x18) = *(int *)(elem + 8);
        i = 0;
        off = 0;
        do {
            *(int *)(*rec_out + off + 0x1c) = ep[0];
            *(int *)(*rec_out + off + 0x20) = ep[1];
            i = i + 1;
            ep = ep + 2;
            off = off + 8;
        } while (i < 0x18);
        return 1;
    }
    return 0;
}
