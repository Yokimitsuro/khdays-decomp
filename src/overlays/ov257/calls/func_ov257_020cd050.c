/* Attack cue helper of the ov257 states: the +0x58 clock advances by dt and, by the owner's kind
 * (+0x1c6), the +0x77 cue counter fires reaction +0x408 at the +4 point once each mark is
 * passed -- kind 8: mode 0x22 at 0.33, 0x23 at 0.93, 0x26 at 2.67; kind 9: 0x27 at once, 0x25
 * at 2.33; kind 0xb: 0x24 at 1.5; kind 0xd: 0x26 at 2.23; kind 0xc: 0x2a at 1.93. */
typedef unsigned char u8;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);

void func_ov257_020cd050(int *state, int dt)
{
    unsigned char cue;

    state[0x16] += dt;
    switch (*(signed char *)(*state + 0x1c6)) {
    case 8:
        cue = *((u8 *)state + 0x77);
        if (cue == 0) {
            if (state[0x16] >= 0x555) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x22, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        } else if (cue == 1) {
            if (state[0x16] >= 0xeee) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x23, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        } else if (cue == 2) {
            if (state[0x16] >= 0x2aaa) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x26, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        }
        break;
    case 9:
        cue = *((u8 *)state + 0x77);
        if (cue == 0) {
            if (state[0x16] >= 0) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x27, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        } else if (cue == 1) {
            if (state[0x16] >= 0x2555) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x25, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        }
        break;
    case 10:
        break;
    case 11:
        if (*((u8 *)state + 0x77) == 0) {
            if (state[0x16] >= 0x1800) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x24, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        }
        break;
    case 13:
        if (*((u8 *)state + 0x77) == 0) {
            if (state[0x16] >= 0x23bb) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x26, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        }
        break;
    case 12:
        if (*((u8 *)state + 0x77) == 0) {
            if (state[0x16] >= 0x1eee) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x2a, (void *)state[1]);
                (*((u8 *)state + 0x77))++;
            }
        }
        break;
    }
}
