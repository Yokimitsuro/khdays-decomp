extern int func_0203c7e8();
extern int func_0203d194();
extern int func_ov107_020c68ec();

struct S {
    char pad[0x384];
    int field_384;
    char pad2[0x390 - 0x384 - 4];
    int *field_390;
};

void func_ov159_020d45d4(struct S *r0)
{
    func_0203c7e8(r0->field_384);
    func_0203c7e8(*r0->field_390);
    func_0203d194(r0->field_390);
    func_ov107_020c68ec(r0);
}
