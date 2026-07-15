/* MsgDb_DecodeGenericRecord (db 0..0x12, index<0x32): fetch the string pair into a
 * fresh 0x3e0 record (func_02034428 + MsgDb_FetchStringPair), then copy the fixed
 * 0x3c0 layout block (24 rows x 0x28) from entry[8] + index*0x3c0 into the record at
 * +0x18. *param_1 (the record ptr) is re-read per store. */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, int size, int db, int keep);
extern int func_02034fc4(short *rec, void *a, void *b, void *c, void *d, int db, int index, int keep);
extern void func_020343cc(int *rec_out);
extern int data_0204c238;
int func_02034e3c(int *param_1, int param_2, unsigned int param_3, int param_4) {
    unsigned int *puVar4;
    short *psVar2;
    int i, off;
    if (func_020342b4(param_2) == 0 || (param_4 >= 0 && *param_1 != 0)) {
        return 0;
    }
    if (param_2 >= 0 && param_2 <= 0x12 && param_3 < 0x32) {
        puVar4 = (unsigned int *)(*(int *)(data_0204c238 + param_2 * 0x14 + 8) + param_3 * 0x3c0);
        if (func_02034428(param_1, 0x3e0, param_2, param_4) == 0 || (psVar2 = (short *)*param_1) == 0) {
            return 0;
        }
        if (func_02034fc4(psVar2, psVar2 + 6, psVar2 + 8, psVar2 + 0x1ec, psVar2 + 0x1ee,
                          param_2, param_3, param_4) == 0) {
            func_020343cc(param_1);
            return 0;
        }
        *(unsigned int *)(*param_1 + 0x14) = param_3;
        i = 0;
        off = 0;
        do {
            *(int *)(*param_1 + off + 0x18) = puVar4[0];
            *(int *)(*param_1 + off + 0x1c) = puVar4[1];
            *(int *)(*param_1 + off + 0x20) = puVar4[2];
            *(int *)(*param_1 + off + 0x24) = puVar4[3];
            *(int *)(*param_1 + off + 0x28) = puVar4[4];
            *(int *)(*param_1 + off + 0x2c) = puVar4[5];
            *(int *)(*param_1 + off + 0x30) = puVar4[6];
            *(int *)(*param_1 + off + 0x34) = puVar4[7];
            *(int *)(*param_1 + off + 0x38) = puVar4[8];
            i = i + 1;
            *(int *)(*param_1 + off + 0x3c) = puVar4[9];
            puVar4 = puVar4 + 10;
            off = off + 0x28;
        } while (i < 0x18);
        return 1;
    }
    return 0;
}
