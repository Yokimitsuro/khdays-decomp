/* func_ov266_020ce9c8 -- the teardown: release everything this object owns, then free the object.
 *
 * One of a 3-member shape family; the twins live in ov212/ov267 and are byte-identical modulo
 * relocs (matched here, fanned out with dedupprop).
 *
 * Releases, in order: the two singles at +0x384 / +0x388; all 16 entries of the stride-4 table at
 * +0x38c; and the non-null entries of the stride-8 table at +0x60c (10 of them -- the only loop
 * here that checks for null first, so that table is allowed to be sparse). Then it destroys the
 * NitroSDK double list at +0x5e4 and hands the object itself to func_ov107_020c68ec.
 *
 * Both loops use the array-index form so mwcc keeps `i` as the only induction variable and folds
 * the table's base offset into the load; `*(int *)(obj + K + i * S)` gets strength-reduced into a
 * walking pointer instead (codegen-cracks.md). The second table's stride is 8, hence `i * 2` on an
 * int index: (i * 2 + 0x183) * 4 == i * 8 + 0x60c. */

typedef struct {
    int a;
    int b;
} Slot8;

typedef struct {
    char pad0[0x60c];
    Slot8 tbl8[10];
} Obj;

extern void func_0203c7e8(int a);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_ov107_020c68ec(int obj);

void func_ov266_020ce9c8(int obj) {
    int i;
    int p;

    func_0203c7e8(*(int *)(obj + 0x384));
    func_0203c7e8(*(int *)(obj + 0x388));
    for (i = 0; i < 0x10; i++) {
        func_0203c7e8(((int *)obj)[i + 0xe3]);
    }
    for (i = 0; i < 0xa; i++) {
        p = ((Obj *)obj)->tbl8[i].a;
        if (p != 0) {
            func_0203c7e8(p);
        }
    }
    NNSi_FndDestroyDoubleList((void *)(obj + 0x5e4));
    func_ov107_020c68ec(obj);
}
