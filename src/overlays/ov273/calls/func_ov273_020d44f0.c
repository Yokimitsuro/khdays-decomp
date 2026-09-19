/* Re-arm the five hit slots (0, 2, 4, 1, 3) of the +0x38c collision handle with the actor's
 * +0x310 kind byte and its +0x311 bit-0 flag. */
extern int func_0203b9fc();

struct S {
    char pad300[0x310];
    signed char b310;
    unsigned char bit0 : 1;
    unsigned char rest : 7;
    char pad312[0x7a];
    void *p38c;
};

void func_ov273_020d44f0(struct S *s) {
    func_0203b9fc(s->p38c, 0, s->b310, s->bit0);
    func_0203b9fc(s->p38c, 2, s->b310, s->bit0);
    func_0203b9fc(s->p38c, 4, s->b310, s->bit0);
    func_0203b9fc(s->p38c, 1, s->b310, s->bit0);
    func_0203b9fc(s->p38c, 3, s->b310, s->bit0);
}
