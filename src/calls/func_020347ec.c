/* MsgDb decoder for db 0x19: bounds-check index, alloc a 0x48 record (kind 0x19),
 * store index + elem[0..3] (note +0x1c/+0x18 order), then copy 5 pairs from elem+0x10
 * into rec+0x20/+0x34 (stride 4). elem = entry[8] + index*0x38 (table + 0x19*0x14). */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int kind, int keep);
extern int data_0204c238;
int func_020347ec(int *rec_out, int index, int keep) {
    int elem;
    int i;
    int *ep;
    int off;
    if (func_020342b4(0x19) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    if (index >= 0 && index < *(unsigned short *)(data_0204c238 + 0x200)) {
        elem = *(int *)(data_0204c238 + 0x1fc) + index * 0x38;
        ep = (int *)(elem + 0x10);
        if (func_02034428(rec_out, 0x48, 0x19, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        *(int *)(*rec_out + 0xc) = index;
        *(int *)(*rec_out + 0x10) = *(int *)elem;
        *(int *)(*rec_out + 0x14) = *(int *)(elem + 4);
        *(int *)(*rec_out + 0x1c) = *(int *)(elem + 8);
        *(int *)(*rec_out + 0x18) = *(int *)(elem + 0xc);
        i = 0;
        off = 0;
        do {
            *(int *)(*rec_out + off + 0x20) = ep[0];
            i = i + 1;
            *(int *)(*rec_out + off + 0x34) = ep[1];
            ep = ep + 2;
            off = off + 4;
        } while (i < 5);
        return 1;
    }
    return 0;
}
