extern int func_02023c40();

struct S {
    char pad0[0xc];
    int field_c;
    short field_10;
    char pad12[2];
    int field_14;
};

void func_ov030_020b4654(struct S *p) {
    p->field_c = 1;
    p->field_14 = 2;
    p->field_10 = (func_02023c40() == 1) ? 0x0f46 : 0x0a2f;
}
