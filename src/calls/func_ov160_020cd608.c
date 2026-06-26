extern int func_02023eb4();
extern int func_0203c634();

struct A { char pad0[4]; struct B *b; char pad8[0x20-8]; signed char field20; };
struct B { unsigned char *field0; struct C *field4; char pad8[0x44-8]; int field44; };
struct C { char pad[0xad]; unsigned char fieldAD; };

void func_ov160_020cd608(struct A *a)
{
    struct B *b = a->b;
    int f44;

    if (b->field4->fieldAD != 0)
        return;

    f44 = b->field44;
    if (f44 <= 0) {
        if (func_02023eb4(2) + (f44 - f44) == 0)
            b->field0[0x1c7] = 7;
        else
            b->field0[0x1c7] = 6;
    } else {
        b->field0[0x1c7] = 2;
    }

    func_0203c634(a, a->field20, 0);
}
