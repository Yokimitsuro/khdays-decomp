extern int func_02023eb4();
extern int func_0203c634();

struct S0 {
    int* field_0;
    char pad[0x224 - 4];
    int field_224;
    int field_228;
};

struct S1 {
    struct S0* field_0;
    char pad4[0x34 - 4];
    int field_34;
    char pad38[0x48 - 0x38];
    unsigned char* field_48;
};

struct S2 {
    char pad0[4];
    struct S1* field_4;
    char pad8[0x20 - 8];
    signed char field_20;
};

void func_ov162_020cf520(struct S2* a) {
    struct S1* b = a->field_4;
    if (*b->field_48 != 0) {
        return;
    }
    {
        struct S0* c = b->field_0;
        int lo = c->field_224;
        int diff = c->field_228 - lo;
        if (diff < 0) diff = -diff;
        b->field_34 = lo + func_02023eb4(diff + 1);
    }
    *(unsigned char*)((char*)b->field_0 + 0x1c7) = 2;
    func_0203c634(a, a->field_20, 0);
}
