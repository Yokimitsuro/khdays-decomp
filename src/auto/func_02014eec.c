struct S {
    unsigned char pad[0x2c];
    int field_2c;
    unsigned short field_30;
    unsigned short field_32;
};

int func_02014eec(struct S *p) {
    int ret;
    p->field_32 &= ~1;
    ret = p->field_2c;
    p->field_2c = 0;
    return ret;
}
