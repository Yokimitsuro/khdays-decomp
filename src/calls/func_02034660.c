/* MsgDb decoder for db 0x16: scan a table of up to 0x276 entries (stride 0x64) for
 * ones whose halfword at offset 6 equals `value`, collecting up to 20 matching
 * 1-based indices. If none match, fail. Otherwise alloc a 0x18-byte record (kind
 * 0x16), store the search value and match count, then allocate and fill an
 * out-of-line array of the matched indices. */
extern int func_020342b4(int db);
extern int func_02034428(int *rec_out, unsigned int size, short kind, int keep);
extern void *NNSi_FndAllocFromDefaultExpHeap(unsigned int size);
extern int func_02035070(int *slot);
extern int data_0204c238;

typedef struct {
    char pad_00[6];
    short field_06;
    char pad_08[0x64 - 8];
} Entry;

typedef struct {
    short keepFlag;
    short kind;
    int field_04;
    int field_08;
    int value;
    int count;
    int *indices;
} Rec16;

int func_02034660(int *rec_out, int value, int keep) {
    int count = 0;
    int j, i;
    int matches[20];

    if (func_020342b4(0x16) == 0 || (keep >= 0 && *rec_out != 0)) {
        return 0;
    }
    for (j = 0; j < 0x276; j++) {
        if (((Entry *)*(int *)(data_0204c238 + 0x1c0))[j].field_06 == value) {
            if (count < 20) {
                matches[count] = j + 1;
            }
            count++;
        }
    }
    if (count > 0) {
        if (func_02034428(rec_out, 0x18, 0x16, keep) == 0 || *rec_out == 0) {
            return 0;
        }
        ((Rec16 *)*rec_out)->value = value;
        ((Rec16 *)*rec_out)->count = count;
        ((Rec16 *)*rec_out)->indices = NNSi_FndAllocFromDefaultExpHeap(count * 4);
        if (((Rec16 *)*rec_out)->indices == 0) {
            func_02035070(rec_out);
            return 0;
        }
        for (i = 0; i < count; i++) {
            ((Rec16 *)*rec_out)->indices[i] = matches[i];
        }
        return 1;
    }
    return 0;
}
