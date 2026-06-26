extern int func_0203b9fc();
extern int func_0203c640();

struct Inner {
    int field0;
    int field4;
    int field8;
    int fieldc;
};

struct Outer {
    struct A *a;
    struct Inner *inner;
};

struct A {
    char pad[0x2c];
    int field2c;
};

void func_ov131_020cecf8(struct Outer *o) {
    struct A *a = o->a;
    struct Inner *in = o->inner;
    in->field8 = a->field2c + in->field8;
    if (in->field8 < 0x1000) {
        return;
    }
    if (in->fieldc == 8) {
        func_0203c640();
        return;
    }
    in->field8 = 0;
    in->fieldc = in->fieldc + 1;
    func_0203b9fc(in->field4, 4, (short)in->fieldc, 1);
}
