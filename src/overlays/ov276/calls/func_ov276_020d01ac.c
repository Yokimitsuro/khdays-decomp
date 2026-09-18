/* Message handler of the ov276 enemy: a "spawned" message (kind 5) unpacks the 24-bit position
 * into a fresh transform and starts the +0x488 sub-item named by the payload under the +0x3c
 * owner (kind 0x17) into +0x48c: payloads 0 (scaled by 0xb33, blend 1), 1 and 4 at the
 * transform with the packet's blend, 2 at the +0x3ec anchor and 3/5 at the +0xa0 transform
 * with the packet's blend; payload 7 registers effect 0x164 (kind 9) on the +0xa0 node into
 * +0x484. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern int func_ov107_020c0794(int model, int parent, int kind, u8 blend, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, u8 blend, int b);
extern int func_ov107_020cb040(int owner, int resourceId, int kind, int zero, void *work);
extern void func_ov107_020c7500(int owner, u8 *msg, int arg);

void func_ov276_020d01ac(int owner, u8 *msg, int arg)
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
            func_0203ca9c(&transform, 0xb33);
        case 1:
        case 4:
            *(int *)(owner + msg[3] * 8 + 0x48c) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x488), 0x17, msg[3] == 0 ? 1 : msg[4], &transform);
            break;
        case 2:
            *(int *)(owner + msg[3] * 8 + 0x48c) =
                func_ov107_020c09a0(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x488), 0x17, (void *)(owner + 0x3ec), msg[4], 0);
            break;
        case 3:
        case 5:
            *(int *)(owner + msg[3] * 8 + 0x48c) =
                func_ov107_020c09a0(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x488), 0x17, (void *)(owner + 0xa0), msg[4], 0);
            break;
        case 6:
            break;
        case 7:
            *(int *)(owner + 0x484) = func_ov107_020cb040(owner, 0x164, 9, 0, (void *)(owner + 0xa0));
            break;
        }
    }
    func_ov107_020c7500(owner, msg, arg);
}
