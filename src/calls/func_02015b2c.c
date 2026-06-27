extern void func_02015924(void *a, void *b);
extern struct { char _0[0xd4]; int field_d4; } data_02047394;
extern char data_0204739c[];
extern char data_0204752c[];

void *func_02015b2c(void)
{
    if ((data_02047394.field_d4 & 0x10) == 0) {
        func_02015924(data_0204739c, data_0204752c);
        data_02047394.field_d4 |= 0x10;
    }
    return data_0204752c;
}
