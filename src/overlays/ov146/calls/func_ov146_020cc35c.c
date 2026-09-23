/* Message handler of the ov146 actor: a spawn message (kind 5) unpacks its position into a transform
 * and starts the +0x3c4 effect pair of the sub id: 0 at the transform scaled 2.0, 1 and 2 at the
 * partner chain's (+0x3b8 of +0x3b8) +0x14 point scaled 2.0 (variant 0 / 2), 4 attached to the actor
 * pose (+0xa0). The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;
struct EffectPair { int res; int handle; };
struct Ov146Effects { char pad[0x3c4]; struct EffectPair pair[8]; };

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern int func_ov107_020c0794(int model, int parent, int kind, int arg, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov146_020cc35c(char *self, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        u8 bytes[12];
    } packed;

    if (msg[2] == 5) {
        packed.bytes[3] = msg[5];
        packed.bytes[2] = msg[6];
        packed.bytes[1] = msg[7];
        translation.x = packed.words[0] >> 8;
        packed.bytes[7] = msg[8];
        packed.bytes[6] = msg[9];
        packed.bytes[5] = msg[0xa];
        translation.y = packed.words[1] >> 8;
        packed.bytes[11] = msg[0xb];
        packed.bytes[10] = msg[0xc];
        packed.bytes[9] = msg[0xd];
        translation.z = packed.words[2] >> 8;
        func_0203c960(&transform);
        func_0203ca30(&transform, &translation);
        switch (msg[3]) {
        case 0:
            func_0203ca9c(&transform, 0x2000);
            ((struct Ov146Effects *)self)->pair[msg[3]].handle = func_ov107_020c0794(
                *(int *)(self + 0x3c), ((struct Ov146Effects *)self)->pair[msg[3]].res, 0x17, 0, &transform);
            break;
        case 1:
        case 2:
            func_0203ca30(&transform, (Vec3 *)(*(int *)(*(int *)(self + 0x3b8) + 0x3b8) + 0x14));
            func_0203ca9c(&transform, 0x2000);
            ((struct Ov146Effects *)self)->pair[msg[3]].handle = func_ov107_020c0794(
                *(int *)(self + 0x3c), ((struct Ov146Effects *)self)->pair[msg[3]].res, 0x17,
                (u8)(msg[3] == 1 ? 0 : 2), &transform);
            break;
        case 4:
            ((struct Ov146Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(
                *(int *)(self + 0x3c), ((struct Ov146Effects *)self)->pair[msg[3]].res, 0x17, self + 0xa0, 0, 0);
            break;
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
