extern unsigned short SND_CalcChannelVolume(int x);
extern void SND_SetChannelVolume(unsigned int chnBitMask, int volume, int chnDataShift);

struct ChnEntry {
    int field_0;
    int field_4;
};

extern struct ChnEntry data_0204ac30[];

struct X {
    char _0[0x3c];
    int field_3c;
    char _40[8];
    int field_48;
    unsigned char field_4c[1];
};

void func_0201ac50(struct X *p, int decibel)
{
    unsigned int chn;
    int ret;
    int i;

    p->field_3c = decibel;
    i = 0;
    if (p->field_48 <= 0) return;

    do {
        chn = p->field_4c[i];
        ret = SND_CalcChannelVolume(p->field_3c + data_0204ac30[chn].field_4);
        SND_SetChannelVolume(1U << chn, ret & 0xff, ret >> 8);
        i++;
    } while (i < p->field_48);
}
