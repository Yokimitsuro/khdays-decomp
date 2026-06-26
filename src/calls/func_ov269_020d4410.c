extern int func_ov107_020c9f48();
extern int func_0202f384();
extern int func_01ffa724();
extern int func_0203c634();

struct S0 { int *f0; int *f4; char pad[0x20 - 8]; signed char f20; };

struct Local { int a; int b; int c; };

void func_ov269_020d4410(struct S0 *this)
{
    struct Local local;
    int *r6 = this->f4;
    int r5;

    r5 = func_ov107_020c9f48(((int **)r6[0])[0xf4], &local);
    func_0202f384((char *)r6 + 0x18, (char *)r6[0] + 0xa0, &local);
    func_01ffa724(r5, (char *)r6 + 0x18, (char *)r6 + 0x18);

    if (*((unsigned char *)((int *)r6[1]) + 0xad) != 0)
        return;

    *((char *)r6[0] + 0x1c7) = 2;
    func_0203c634(this, (int)*((signed char *)this + 0x20), 0);
}
