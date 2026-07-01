struct A { char pad0[4]; int *p; };
struct B { char pad0[4]; struct C *p; };
struct C { char pad[0x5c]; int flag; };

int func_ov278_020d5eb0(struct B **arg0) {
    struct C *q = arg0[1]->p;
    return q->flag |= 2;
}
