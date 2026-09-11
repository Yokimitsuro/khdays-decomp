extern void func_0203c7e8(int obj);
extern void func_ov107_020c68ec(int obj);

typedef struct {
    int field_00;
    int field_04;
} Pair8;

void func_ov248_020d03cc(int obj) {
    int i;
    for (i = 0; i < 2; i++) {
        func_0203c7e8(((Pair8 *)obj)[i + 0x71].field_00);
    }
    func_ov107_020c68ec(obj);
}
