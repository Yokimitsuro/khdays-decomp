extern void func_02001f10(void *p);
extern struct { char _0[4]; char *field_4; char _8[0x34]; int field_3c; } data_0204bbfc;

int func_0201ef58(void)
{
    if (data_0204bbfc.field_3c <= 0) {
        if (*(int *)(data_0204bbfc.field_4 + 0x448) == 0) goto out;
    }
    func_02001f10(data_0204bbfc.field_4 + 0x4c + 0x400);
out:
    return 1;
}
