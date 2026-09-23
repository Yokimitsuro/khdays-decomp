/* Message handler of the ov258 actor: kind 0 stores the message's vortex time (+0x24) in +0x428; a
 * spawn message (kind 5) starts the +0x464 effect of its sub id: 0-5 and 10 on the actor transform,
 * 0x17 / 0x18 on the +0x44c / +0x450 hands, the positional ones (6-9, 11, 0x16, 0x21-0x25, 0x28-0x29) at
 * the message position (bank 5 / 0xd / 0x17, scale 1.0 for 6, 7 and 0x16 else 3.0); 12 and 0x1b fill the
 * first free shot (020d06a0, ten from 12) or burst (020d0a5c, six from 0x1b) slot (the slot index is passed on), 0x19 / 0x1a spawn a
 * beam (020d0dbc) and 0x2a a marker (020d14e4, +0x5b8) at the position. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct EffectPair { int res; int handle; };
struct Ov258Effects { char pad[0x464]; struct EffectPair pair[0x30]; };

extern int func_ov107_020c09a0(int model, int res, u8 kind, void *at, int a, int b);
extern int func_ov107_020c08cc(int model, int res, u8 kind, int arg, int scale, u8 *pos);
extern int func_ov258_020d14e4(char *self, int rig, Vec3 *pos);
extern int func_ov258_020d06a0(char *self, int rig, Vec3 *pos, int slot);
extern int func_ov258_020d0a5c(char *self, int rig, Vec3 *pos, int slot);
extern int func_ov258_020d0dbc(char *self, int rig, Vec3 *pos, int kind);
extern int func_ov107_020c7500(char *self, u8 *msg, int arg);

static inline void UnpackPosition(Vec3 *out, const u8 *msg)
{
    union {
        int words[3];
        u8 bytes[12];
    } packed;

    packed.bytes[3] = msg[5];
    packed.bytes[2] = msg[6];
    packed.bytes[1] = msg[7];
    out->x = packed.words[0] >> 8;
    packed.bytes[7] = msg[8];
    packed.bytes[6] = msg[9];
    packed.bytes[5] = msg[0xa];
    out->y = packed.words[1] >> 8;
    packed.bytes[11] = msg[0xb];
    packed.bytes[10] = msg[0xc];
    packed.bytes[9] = msg[0xd];
    out->z = packed.words[2] >> 8;
}

int func_ov258_020cc5e8(char *self, u8 *msg, int arg)
{
    Vec3 pos;
    signed char j;

    if (msg[2] == 0) {
        *(int *)(self + 0x428) = *(int *)(msg + 0x24);
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            ((struct Ov258Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov258Effects *)self)->pair[msg[3]].res,
                                                      msg[3] == 0xc ? 1 : 5, self + 0xa0, msg[4], 0);
            break;
        case 10:
            ((struct Ov258Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov258Effects *)self)->pair[msg[3]].res, 5, self + 0xa0, msg[4], 0);
            break;
        case 6:
        case 7:
        case 8:
        case 9:
        case 11:
        case 0x16:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x28:
        case 0x29:
        {
            u8 kind = msg[3] >= 0x28 ? 0x17 : (msg[3] >= 0x21 ? 0xd : 5);
            int scale = (msg[3] == 6 || msg[3] == 7 || msg[3] == 0x16) ? 0x1000 : 0x3000;

            ((struct Ov258Effects *)self)->pair[msg[3]].handle = func_ov107_020c08cc(
                *(int *)(self + 0x3c), ((struct Ov258Effects *)self)->pair[msg[3]].res, kind, 0, scale, msg + 5);
        }
            break;
        case 0x2a:
            UnpackPosition(&pos, msg);
            *(int *)(self + 0x5b8) = func_ov258_020d14e4(self, *(int *)(self + 0x5b4), &pos);
            break;
        case 12:
            for (j = 0; j < 10; j++) {
                if (((struct Ov258Effects *)self)->pair[j + 0xc].handle == 0) {
                    break;
                }
            }
            if (j == 10) {
                break;
            }
            UnpackPosition(&pos, msg);
            ((struct Ov258Effects *)self)->pair[j + 0xc].handle = func_ov258_020d06a0(self, ((struct Ov258Effects *)self)->pair[j + 0xc].res, &pos, j);
            break;
        case 0x17:
            ((struct Ov258Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov258Effects *)self)->pair[msg[3]].res, 5,
                                                      (void *)(*(int *)(self + 0x44c) + 4), msg[4], 0);
            break;
        case 0x18:
            ((struct Ov258Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(*(int *)(self + 0x3c), ((struct Ov258Effects *)self)->pair[msg[3]].res, 5,
                                                      (void *)(*(int *)(self + 0x450) + 4), msg[4], 0);
            break;
        case 0x1b:
            for (j = 0; j < 6; j++) {
                if (((struct Ov258Effects *)self)->pair[j + 0x1b].handle == 0) {
                    break;
                }
            }
            if (j == 6) {
                break;
            }
            UnpackPosition(&pos, msg);
            ((struct Ov258Effects *)self)->pair[j + 0x1b].handle = func_ov258_020d0a5c(self, ((struct Ov258Effects *)self)->pair[j + 0x1b].res, &pos, j);
            break;
        case 0x19:
        case 0x1a:
            UnpackPosition(&pos, msg);
            ((struct Ov258Effects *)self)->pair[msg[3]].handle = func_ov258_020d0dbc(self, ((struct Ov258Effects *)self)->pair[msg[3]].res, &pos, (signed char)msg[3]);
            break;
        }
    }
    return func_ov107_020c7500(self, msg, arg);
}
