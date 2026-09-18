/* Message handler of the ov240 enemy: a "spawned" message (kind 5) unpacks the 24-bit position
 * into a fresh transform and starts the +0x39c sub-item named by the payload (0-2 with kind
 * 0x15, blend 1 for payload 2, 3 with kind 5, 4 with kind 0x15) under the +0x3c owner into +0x3a0. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, u8 blend, SrtTransform *transform);
extern void func_ov107_020c7500(int owner, u8 *msg, int arg);

void func_ov240_020ce138(int owner, u8 *msg, int arg)
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
        case 1:
        case 2:
            *(int *)(owner + msg[3] * 8 + 0x3a0) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x39c), 0x15, msg[3] == 2 ? 1 : 0, &transform);
            break;
        case 3:
            *(int *)(owner + msg[3] * 8 + 0x3a0) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x39c), 5, 0, &transform);
            break;
        case 4:
            *(int *)(owner + msg[3] * 8 + 0x3a0) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x39c), 0x15, 0, &transform);
            break;
        }
    }
    func_ov107_020c7500(owner, msg, arg);
}
