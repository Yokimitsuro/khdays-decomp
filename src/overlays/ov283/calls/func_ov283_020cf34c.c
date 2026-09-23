/* Message handler of the ov283 actor: a spawn message (kind 5) unpacks its position into a transform
 * and, for sub 0, starts the +0x390 effect pair there (kind 0xf). The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;
struct EffectPair { int res; int handle; };
struct Ov283Effects { char pad[0x390]; struct EffectPair pair[1]; };

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int arg, SrtTransform *transform);
extern void func_ov107_020c7500(char *self, u8 *msg, int arg);

void func_ov283_020cf34c(char *self, u8 *msg, int arg)
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
        if (msg[3] == 0) {
            ((struct Ov283Effects *)self)->pair[msg[3]].handle = func_ov107_020c0794(
                *(int *)(self + 0x3c), ((struct Ov283Effects *)self)->pair[msg[3]].res, 0xf, 0, &transform);
        }
    }
    func_ov107_020c7500(self, msg, arg);
}
