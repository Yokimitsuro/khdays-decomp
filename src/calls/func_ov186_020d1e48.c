extern int func_0203cd7c();
extern int func_0202ea48();
extern int data_02042264;

struct S {
    char pad0[4];
    int *field_4;
    char pad8[0x3c];
    int field_44;
};

void func_ov186_020d1e48(struct S *r0, int r1)
{
    char local[0x24];
    func_0203cd7c(local, (char *)r0->field_4 + 0x74, r0->field_44, &data_02042264);
    func_0202ea48(r1, local);
}
