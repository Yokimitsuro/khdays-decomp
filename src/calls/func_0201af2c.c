extern void SND_SetChannelVolume(unsigned int chnBitMask, int volume, int chnDataShift);
extern void func_0201afac(void);
extern int func_0201e16c(void *p);
extern void func_0201e1a0(void *p);
extern int func_0201e1b8(void *p);

typedef struct {
    int field_0;
    int field_4;
    char _8[0x1c];
    unsigned int field_24;
    char _28[0x14];
    char field_3c[0x10];
    int field_4c;
    int field_50;
} Data_0204acf8;

extern Data_0204acf8 data_0204acf8;

void func_0201af2c(void)
{
    Data_0204acf8 *p = &data_0204acf8;
    int v;

    if (p->field_0 == 0) return;
    if (p->field_4 != 0) return;

    func_0201e1a0(p->field_3c);

    if (p->field_4c != 0) {
        if (func_0201e1b8(p->field_3c) != 0) {
            func_0201afac();
            return;
        }
    }

    v = func_0201e16c(p->field_3c) >> 8;
    if (v == p->field_50) return;

    SND_SetChannelVolume(p->field_24, v, 0);
    p->field_50 = v;
}
