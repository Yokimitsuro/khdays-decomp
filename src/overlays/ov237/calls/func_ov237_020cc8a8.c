/* Message handler of the ov237 actor: a spawn message (kind 5) starts the +0x490 effect pair of its
 * sub id: bank 0x17 at the message position (scale 1.0) for 0-3, 8, 0xd, 0xe and 0x12; on the +0x454 /
 * +0x458 hands (4 / 5) or the +0x45c transform (6); bank 0xd on the actor transform for 9-12; bank
 * 0x1f at the position for 0xf / 0x11 or on the actor for 0x10; 7 emits a spark at the position
 * (+0x3e8 emitter, 4.0), 0x14 starts effect set 1 and 0x15 creates the +0x498 item (0x12d, 0xb). The
 * base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct EffectPair { int res; int handle; };

extern int func_ov107_020c08cc(int model, int res, int kind, int arg, int scale, u8 *pos);
extern int func_ov107_020c09a0(int model, int res, int kind, void *at, int a, int b);
extern void func_ov237_020d1598(void *emitter, Vec3 *pos, int value);
extern void func_ov107_020c0b14(char *self, int set);
extern int func_ov107_020cb040(char *self, int bank, int variant, int a, void *at);
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

int func_ov237_020cc8a8(char *self, u8 *msg, int arg)
{
    Vec3 pos;

    if (msg[2] != 0 && msg[2] == 5) {
        switch (msg[3]) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 8:
        case 0xd:
        case 0xe:
        case 0x12:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c08cc(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0x17, 0, 0x1000, msg + 5);
            break;
        case 4:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0x17,
                (void *)(*(int *)(self + 0x454) + 4), msg[4], 0);
            break;
        case 5:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0x17,
                (void *)(*(int *)(self + 0x458) + 4), msg[4], 0);
            break;
        case 6:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0x17,
                self + 0x45c, msg[4], 0);
            break;
        case 0xf:
        case 0x11:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c08cc(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0x1f, 0, 0x1000, msg + 5);
            break;
        case 9:
        case 10:
        case 11:
        case 12:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0xd,
                self + 0xa0, msg[4], 0);
            break;
        case 0x10:
            (*(struct EffectPair **)(self + 0x490))[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), (*(struct EffectPair **)(self + 0x490))[msg[3]].res, 0x1f,
                self + 0xa0, msg[4], 0);
            break;
        case 7:
            UnpackPosition(&pos, msg);
            func_ov237_020d1598(*(void **)(self + 0x3e8), &pos, 0x4000);
            break;
        case 0x14:
            func_ov107_020c0b14(self, 1);
            break;
        case 0x15:
            *(int *)(self + 0x498) = func_ov107_020cb040(self, 0x12d, 0xb, 1, self + 0xa0);
            break;
        }
    }
    return func_ov107_020c7500(self, msg, arg);
}
