extern void *func_020158e0(void);
extern void *func_02015b2c(void);
extern void MTX_Copy43To44_(const void *src, void *dst);
extern void MTX_Concat44(const void *a, const void *b, void *out);

extern struct { char _0[0xd4]; int field_d4; } data_02047394;
extern char data_0204756c[];

void *func_02015c38(void) {
    int m44[0x10];

    if (!(data_02047394.field_d4 & 0x40)) {
        void *m43 = func_020158e0();
        void *m44_src = func_02015b2c();

        MTX_Copy43To44_(m43, m44);
        MTX_Concat44(m44_src, m44, data_0204756c);
        data_02047394.field_d4 |= 0x40;
    }

    return data_0204756c;
}
