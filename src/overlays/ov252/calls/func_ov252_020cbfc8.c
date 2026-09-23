/* Animation tick of an ov252 model: a frozen model (+0x5c bit 1) only runs the base tick while it is
 * shown (+0x60). Otherwise the base tick runs (0203c904) and, unless the +0x88 header says static
 * (bit 1), each of the five channels that is playing (+0xad[i]) with a clip (header[i + 1] >= 0)
 * finds its track in the first of the owner's four banks (+0x3a0, 0x24 each) that has it, advances
 * it by rate x the channel speed (+0x94[i]), forward or backward (+0xb2 bit 0), and at the end
 * wraps when looping (+0xa8[i]) or clamps and stops. */
typedef unsigned char u8;
typedef unsigned short u16;
struct Flags5c { int b0 : 1; int b1 : 1; };
struct Flag { u8 b0 : 1; };
typedef struct { int frame; int pad; char *clip; } Track;
typedef struct { short count[8]; Track **tracks[5]; } AnimBank;

extern void func_0203c904(char *self, int rate);

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void func_ov252_020cbfc8(char *self, int rate)
{
    char *owner = *(char **)(self + 0x84);
    long i;
    int k;

    if (((struct Flags5c *)(self + 0x5c))->b1) {
        if (*(u8 *)(self + 0x60) == 0) {
            return;
        }
        func_0203c904(self, rate);
        return;
    }
    func_0203c904(self, rate);
    if (**(u16 **)(self + 0x88) & 2) {
        return;
    }
    for (i = 0; i < 5; i++) {
        int clip = (*(short **)(self + 0x88))[i + 1];

        if (*(u8 *)(self + i + 0xad) != 0 && clip >= 0) {
            Track *track = 0;
            AnimBank *bank = (AnimBank *)(owner + 0x3a0);
            int step;
            int end;

            for (k = 0; k < 4 && track == 0; bank++, k++) {
                if (bank->tracks[i] != 0 && clip < bank->count[i]) {
                    track = bank->tracks[i][clip];
                }
            }
            end = *(u16 *)(track->clip + 4) << 12;
            step = FX_MUL(rate, ((int *)(self + 0x94))[i]);
            if (!((struct Flag *)(self + 0xb2))->b0) {
                track->frame += step;
                if (track->frame >= end - 0x1000) {
                    if (*(u8 *)(self + i + 0xa8) != 0) {
                        track->frame = 0;
                    } else {
                        track->frame = end - 0x1000;
                        *(u8 *)(self + i + 0xad) = 0;
                    }
                }
            } else {
                track->frame -= step;
                if (track->frame <= 0) {
                    if (*(u8 *)(self + i + 0xa8) != 0) {
                        track->frame = end - 0x1000;
                    } else {
                        track->frame = 0;
                        *(u8 *)(self + i + 0xad) = 0;
                    }
                }
            }
        }
    }
}
