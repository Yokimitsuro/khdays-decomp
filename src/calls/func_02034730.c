/* MsgDb decoder for db 0x13: index-1 based; bounds-check, alloc a 0x30 record, fetch
 * the string pair (MsgDb_FetchStringPair), then store index and 4 bytes from the
 * per-entry table (pb[0],pb[1],pb[3] as words, pb[2] as a byte). pb = entry[8] +
 * (index-1)*4 (table + 0x13*0x14). */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int func_02034fc4(short *rec, void *a, void *b, void *c, void *d, int db, int index, int keep);
extern void func_020343cc(int *rec_out);
extern int data_0204c238;
int func_02034730(int *rec_out, int index, int keep) {
    int iv = index - 1;
    unsigned char *pb;
    short *rec;
    if (func_020342b4(0x13) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (iv >= 0 && iv < *(unsigned short *)(data_0204c238 + 0x188)) {
        pb = (unsigned char *)(*(int *)(data_0204c238 + 0x184) + iv * 4);
        if (func_02034428(rec_out, 0x30, 0x13, keep) == 0 || (rec = (short *)*rec_out) == 0) {
            return 0;
        }
        if (func_02034fc4(rec, rec + 6, rec + 8, rec + 0x14, rec + 0x16, 0x13, iv, keep) == 0) {
            func_020343cc(rec_out);
            return 0;
        }
        *(int *)(*rec_out + 0x14) = index;
        *(unsigned int *)(*rec_out + 0x18) = pb[0];
        *(unsigned int *)(*rec_out + 0x1c) = pb[1];
        *(unsigned int *)(*rec_out + 0x20) = pb[3];
        *(unsigned char *)(*rec_out + 0x24) = pb[2];
        return 1;
    }
    return 0;
}
