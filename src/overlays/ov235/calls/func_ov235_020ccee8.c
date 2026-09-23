/* Attack cue helper of the ov235 states: the +0x80 clock advances by dt and, by the owner's kind
 * (+0x1c6), the +0x64 cue counter fires reaction +0x3c8 at the +4 point once each mark is
 * passed -- kind 8: mode 0x22 at 0.13, 0x23 at 1.2, 0x26 at 2.33; kind 9: 0x27 at once, 0x25
 * at 2.33; kind 0xb: 0x24 at 1.5; kind 0xc: 0x26 at 1.93, 0x28 at 5.0. */
typedef unsigned char u8;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);

void func_ov235_020ccee8(int *state, int dt)
{
    unsigned char cue;

    state[0x20] += dt;
    switch (*(signed char *)(*state + 0x1c6)) {
    case 8:
        cue = *((u8 *)state + 0x64);
        if (cue == 0) {
            if (state[0x20] >= 0x222) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x22, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        } else if (cue == 1) {
            if (state[0x20] >= 0x1333) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x23, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        } else if (cue == 2) {
            if (state[0x20] >= 0x2555) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x26, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        }
        break;
    case 9:
        cue = *((u8 *)state + 0x64);
        if (cue == 0) {
            if (state[0x20] >= 0) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x27, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        } else if (cue == 1) {
            if (state[0x20] >= 0x2555) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x25, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        }
        break;
    case 10:
        break;
    case 11:
        if (*((u8 *)state + 0x64) == 0) {
            if (state[0x20] >= 0x1800) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x24, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        }
        break;
    case 12:
        cue = *((u8 *)state + 0x64);
        if (cue == 0) {
            if (state[0x20] >= 0x1eee) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x26, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        } else if (cue == 1) {
            if (state[0x20] >= 0x5000) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3c8), 0x28, (void *)state[1]);
                (*((u8 *)state + 0x64))++;
            }
        }
        break;
    }
}
