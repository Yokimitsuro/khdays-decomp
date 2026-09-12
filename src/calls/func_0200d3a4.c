extern int func_0200cf10(int param_1);
extern int PXIi_RouteByChannelId(int, void *, void *);
extern int func_0200d0b0(int value);

extern struct { char _0[0x10]; int field_10; int field_14; } data_020463cc;

int func_0200d3a4(int mode, int chan, int useTimeout, int useRoute)
{
    volatile unsigned short *reg_powcnt1 = (volatile unsigned short *)0x04000304;

    if (mode != 0) {
        if (mode == 1) {
            if (useTimeout == 0) {
                if ((unsigned int)(*(int *)0x027ffc3c - data_020463cc.field_10) <= 7) {
                    return 0;
                }
            }

            if (chan != 0) {
                if (useRoute != 0) {
                    func_0200cf10(chan);
                } else {
                    PXIi_RouteByChannelId(chan, 0, 0);
                }
            }
            *reg_powcnt1 |= 1;
            func_0200d0b0(data_020463cc.field_14);
        }
    } else {
        func_0200d0b0(0);
        *reg_powcnt1 &= ~1;
        data_020463cc.field_10 = *(int *)0x027ffc3c;
        if (chan != 0) {
            if (useRoute != 0) {
                func_0200cf10(chan);
            } else {
                PXIi_RouteByChannelId(chan, 0, 0);
            }
        }
    }
    return 1;
}
