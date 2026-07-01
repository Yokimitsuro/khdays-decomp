extern int func_ov107_020c9ec8();
extern int func_ov107_020c6980();

struct S { char pad[0x388]; int field_388; };

int func_ov265_020d00f4(struct S *a, int b) {
    func_ov107_020c9ec8(a->field_388);
    return func_ov107_020c6980(a, b);
}
