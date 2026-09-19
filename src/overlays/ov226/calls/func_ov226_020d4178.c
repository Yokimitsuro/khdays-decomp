/* Item message handler of the ov226 enemy: a kind-0 message, outside owner mode 1, copies its
 * 0x24 flag into bit 1 of the +0x384 sub-item's +0x5c; a "spawned" message (kind 5) unpacks the
 * 24-bit position into a fresh transform and, for slot 0 only, starts the +0x394 sub-item under
 * the +0x3c owner with kind 5 into +0x398. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;
struct b2 { int b0 : 1, b1 : 1; };

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern void func_ov107_020c7500(int owner, u8 *msg, int arg);

void func_ov226_020d4178(int owner, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        u8 bytes[12];
    } packed;

    if (msg[2] == 0) {
        if (*(int *)(owner + 0x50) != 1) {
            ((struct b2 *)(*(int *)(owner + 0x384) + 0x5c))->b1 = msg[0x24];
        }
    } else if (msg[2] == 5) {
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
            *(int *)(owner + msg[3] * 8 + 0x398) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x394), 5, 0, &transform);
        }
    }
    func_ov107_020c7500(owner, msg, arg);
}
