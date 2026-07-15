/* MsgDb decoder for db 0x1f: bounds-check index, alloc a 0x3c record (kind 0x1f),
 * store index + elem[0..2] and copy 4 pairs (stride 8) from elem+0xc into rec+0x1c.
 * elem = entry[8] + index*0x2c (entry at table + 0x1f*0x14). */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;
int func_02034c04(int *rec_out, int index, int keep) {
    int elem;
    int *ep;
    int i, off;
    if (func_020342b4(0x1f) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0 && index < *(unsigned short *)(data_0204c238 + 0x278)) {
        elem = *(int *)(data_0204c238 + 0x274) + index * 0x2c;
        ep = (int *)(elem + 0xc);
        if (func_02034428(rec_out, 0x3c, 0x1f, keep) == 0 || *rec_out == 0) {
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
            i = i + 1;
            *(int *)(*rec_out + off + 0x20) = ep[1];
            ep = ep + 2;
            off = off + 8;
        } while (i < 4);
        return 1;
    }
    return 0;
}
