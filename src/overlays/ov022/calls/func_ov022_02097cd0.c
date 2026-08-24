#pragma opt_common_subs off

struct ResourceTable_02097cd0 {
    unsigned char raw000[0x24];
};

struct Obj_02097cd0 {
    unsigned char pad000[0x2ac0];
    struct ResourceTable_02097cd0 tables2ac0[6];
    void *allocations2b98[6];
};

extern void func_0202a440(struct ResourceTable_02097cd0 *table);
extern void NNSi_FndFreeFromDefaultHeap(void *allocation);

void func_ov022_02097cd0(struct Obj_02097cd0 *arg0) {
    int i = 0;
    struct ResourceTable_02097cd0 *e = arg0->tables2ac0;
    do {
        if (arg0->allocations2b98[i] != 0) {
            func_0202a440(e);
            NNSi_FndFreeFromDefaultHeap(arg0->allocations2b98[i]);
        }
        i++;
        e++;
    } while (i < 6);
}
