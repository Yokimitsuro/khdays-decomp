extern int func_0202a440();
extern int func_0203c7e8();
extern int func_ov107_020c9eac();
extern int func_ov107_020c68ec();

struct Elem {
    int val;
    int pad;
};

struct Obj {
    char pad0[0x384];
    int field_384;   /* 0x384 */
    int field_388;   /* 0x388 */
    char pad1[8];
    int field_394;   /* 0x394 */
    char pad2[0x3fc - 0x394 - 4];
    int field_3fc;   /* 0x3fc */
    char pad3[0x424 - 0x3fc - 4];
    struct Elem arr[8]; /* 0x424, stride 8 bytes */
};

void func_ov223_020d020c(struct Obj *r5)
{
    int i;

    func_0202a440(&r5->field_388);
    r5->field_394 = 0;
    func_0203c7e8(r5->field_384);
    func_ov107_020c9eac(r5->field_3fc);

    for (i = 0; i < 8; i++) {
        if (r5->arr[i].val != 0) {
            func_0203c7e8(r5->arr[i].val);
        }
    }

    func_ov107_020c68ec(r5);
}
