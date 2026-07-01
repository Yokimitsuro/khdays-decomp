extern int func_0203b9fc();
extern int func_0203c7ac();

struct S {
    char pad300[0x310];
    signed char b310;
    unsigned char bit0 : 1;
    unsigned char rest : 7;
    char pad312[0x72];
    void *p384;
};

int func_ov230_020d5e6c(struct S *s) {
    func_0203b9fc(s->p384, 0, s->b310, s->bit0);
    func_0203b9fc(s->p384, 2, s->b310, s->bit0);
    func_0203b9fc(s->p384, 4, s->b310, s->bit0);
    func_0203b9fc(s->p384, 1, s->b310, s->bit0);
    return func_0203c7ac(s->p384, 0);
}
