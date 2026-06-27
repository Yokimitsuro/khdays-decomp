extern void MTX_Inverse43(const void *src, void *dst);

extern struct { char _0[0xd4]; int field_d4; } data_02047394;
extern char data_020473e0;
extern char data_0204746c;

void *func_020158e0(void) {
    if (!(data_02047394.field_d4 & 8)) {
        MTX_Inverse43(&data_020473e0, &data_0204746c);
        data_02047394.field_d4 |= 8;
    }
    return &data_0204746c;
}
