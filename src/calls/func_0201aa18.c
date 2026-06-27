extern void func_02019d00(void *p);

struct S0201aa18 {
    char _0[0x44];
    void *field_44;
    void *field_48;
};

void func_0201aa18(struct S0201aa18 *p)
{
    if (p->field_44 == 0) return;
    func_02019d00(p->field_44);
    p->field_44 = 0;
    p->field_48 = 0;
}
