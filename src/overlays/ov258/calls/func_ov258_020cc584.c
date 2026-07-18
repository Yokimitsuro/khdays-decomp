struct S { char buf[0x24]; int last; };
struct A { char pad24[0x24]; void (*fn)(struct A *, struct S *, int); char pad28[0x428 - 0x28]; int field394; };
void func_ov258_020cc584(struct A *a) {
    struct S s = {0};
    s.buf[2] = 0;
    s.last = a->field394;
    if (a->fn == 0) return;
    a->fn(a, &s, 0x28);
}
