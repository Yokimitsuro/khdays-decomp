/* Message handler of the ov283 actor: a spawn message (kind 5) unpacks its position into a transform
 * and starts the +0x3ec effect pair of the sub id: 0 and 1 at the position scaled 2.0, 2 and 4 on
 * the left hand (+0x394), 3 and 5 on the right hand (+0x398). The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[11]; } SrtTransform;
struct EffectPair { int res; int handle; };
struct Ov283Effects { char pad[0x3ec]; struct EffectPair pair[6]; };

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern int func_ov107_020c0794(int model, int parent, int kind, int arg, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
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

int func_ov283_020cc3ac(char *self, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;

    if (msg[2] == 5) {
        UnpackPosition(&translation, msg);
        func_0203c960(&transform);
        func_0203ca30(&transform, &translation);
        switch (msg[3]) {
        case 0:
        case 1:
            func_0203c960(&transform);
            func_0203ca9c(&transform, 0x2000);
            UnpackPosition(&translation, msg);
            func_0203ca30(&transform, &translation);
            ((struct Ov283Effects *)self)->pair[msg[3]].handle = func_ov107_020c0794(
                *(int *)(self + 0x3c), ((struct Ov283Effects *)self)->pair[msg[3]].res, 0x17, 0, &transform);
            break;
        case 2:
        case 3:
            if (msg[3] == 2) {
                ((struct Ov283Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(
                    *(int *)(self + 0x3c), ((struct Ov283Effects *)self)->pair[msg[3]].res, 5,
                    (void *)(*(int *)(self + 0x394) + 4), 0, 0);
            } else {
                ((struct Ov283Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(
                    *(int *)(self + 0x3c), ((struct Ov283Effects *)self)->pair[msg[3]].res, 5,
                    (void *)(*(int *)(self + 0x398) + 4), 0, 0);
            }
            break;
        case 4:
        case 5:
            if (msg[3] == 4) {
                ((struct Ov283Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(
                    *(int *)(self + 0x3c), ((struct Ov283Effects *)self)->pair[msg[3]].res, 5,
                    (void *)(*(int *)(self + 0x394) + 4), 0, 0);
            } else {
                ((struct Ov283Effects *)self)->pair[msg[3]].handle = func_ov107_020c09a0(
                    *(int *)(self + 0x3c), ((struct Ov283Effects *)self)->pair[msg[3]].res, 5,
                    (void *)(*(int *)(self + 0x398) + 4), 0, 0);
            }
            break;
        }
    }
    return func_ov107_020c7500(self, msg, arg);
}
