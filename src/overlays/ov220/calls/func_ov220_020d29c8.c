extern int func_0203c634();

struct S {
    char pad0[4];
    unsigned char **p4;
    char pad8[0x18];
    signed char b20;
};

int func_ov220_020d29c8(struct S *r0) {
    (*r0->p4)[0x1c7] = 2;
    return func_0203c634(r0, r0->b20, 0);
}
