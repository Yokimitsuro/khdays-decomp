extern void SND_SetChannelPan(unsigned int channelMask, int pan);

struct X {
    char _0[0x48];
    int field_48;
    unsigned char field_4c[1];
};

void func_0201acbc(struct X *p, int idx, int pan) {
    if (idx > p->field_48 - 1) return;
    SND_SetChannelPan(1U << p->field_4c[idx], pan);
}
