/* Message handler of the ov297 enemy: a "spawned" message (kind 5): payload 0 builds a fresh
 * transform scaled by 2.0 at the packet's 24-bit position and starts the +0x398 sub-item of
 * that slot under the +0x3c owner (kind 0x17, the packet's blend) into +0x39c; payload 1 does the
 * same unscaled with kind 7 and no blend. The base handler
 * always runs. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, u8 blend, SrtTransform *transform);
extern void func_ov107_020c7500(int owner, u8 *msg, int arg);

void func_ov297_020d3af4(int owner, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;

    if (msg[2] == 5) {
        switch (msg[3]) {
        case 0: {
            union {
                int words[3];
                u8 bytes[12];
            } packed;
            func_0203c960(&transform);
            func_0203ca9c(&transform, 0x2000);
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
            func_0203ca30(&transform, &translation);
            *(int *)(owner + msg[3] * 8 + 0x39c) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x398), 0x17, msg[4], &transform);
            break;
        }
        case 1: {
            union {
                int words[3];
                u8 bytes[12];
            } packed;
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
            *(int *)(owner + msg[3] * 8 + 0x39c) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x398), 7, 0, &transform);
            break;
        }
        }
    }
    func_ov107_020c7500(owner, msg, arg);
}
