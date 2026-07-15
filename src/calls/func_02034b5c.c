/* MsgDb decoder for db 0x1e: bounds-check index (signed) against the entry count
 * (table + 0x1e*0x14 + 0xc = +0x264), alloc a 0x3c record (kind 0x1e), store index
 * then elem[0..10] into rec+0x10..0x38. elem = entry[8] + index*0x2c. */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;
int func_02034b5c(int *rec_out, int index, int keep) {
    int *elem;
    if (func_020342b4(0x1e) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0 && index < *(unsigned short *)(data_0204c238 + 0x264)) {
        elem = (int *)(*(int *)(data_0204c238 + 0x260) + index * 0x2c);
        if (func_02034428(rec_out, 0x3c, 0x1e, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        *(int *)(*rec_out + 0xc) = index;
        *(int *)(*rec_out + 0x10) = elem[0];
        *(int *)(*rec_out + 0x14) = elem[1];
        *(int *)(*rec_out + 0x18) = elem[2];
        *(int *)(*rec_out + 0x1c) = elem[3];
        *(int *)(*rec_out + 0x20) = elem[4];
        *(int *)(*rec_out + 0x24) = elem[5];
        *(int *)(*rec_out + 0x28) = elem[6];
        *(int *)(*rec_out + 0x2c) = elem[7];
        *(int *)(*rec_out + 0x30) = elem[8];
        *(int *)(*rec_out + 0x34) = elem[9];
        *(int *)(*rec_out + 0x38) = elem[10];
        return 1;
    }
    return 0;
}
