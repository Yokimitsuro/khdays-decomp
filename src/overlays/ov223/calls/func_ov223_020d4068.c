/* Message handler of the ov223 enemy. A kind-0 message, outside owner mode 1, unpacks its
 * 24-bit position (bytes 0x24..0x2c) into the +0xbc anchor and offsets the +0xa0 pose by it
 * (0203ca74). A "spawned" message (kind 5) with slot 0 unpacks the 0x5 position into a fresh
 * transform and starts the +0x398 sub-item under the +0x3c owner with kind 0x17 into +0x39c;
 * with slot 2 the 0x14 position goes to the +0x390 ring's writer (ov223 4e70) along with the
 * message's +4 pose. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;
typedef struct { int q[4]; } Quat;
typedef union { int words[3]; u8 bytes[12]; } Packed;

extern void func_0203ca74(void *pose, const Vec3 *offset);
extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern void func_ov223_020d4e70(int *ring, const Vec3 *pPoint, const Quat *pPose);
extern void func_ov107_020c7500(int owner, u8 *msg, int arg);

void func_ov223_020d4068(int owner, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    Packed anchor;
    Packed spawn;
    Packed ring;

    if (msg[2] == 0) {
        if (*(int *)(owner + 0x50) != 1) {
            anchor.bytes[3] = msg[0x24];
            anchor.bytes[2] = msg[0x25];
            anchor.bytes[1] = msg[0x26];
            *(int *)(owner + 0xbc) = anchor.words[0] >> 8;
            anchor.bytes[7] = msg[0x27];
            anchor.bytes[6] = msg[0x28];
            anchor.bytes[5] = msg[0x29];
            *(int *)(owner + 0xc0) = anchor.words[1] >> 8;
            anchor.bytes[11] = msg[0x2a];
            anchor.bytes[10] = msg[0x2b];
            anchor.bytes[9] = msg[0x2c];
            *(int *)(owner + 0xc4) = anchor.words[2] >> 8;
            func_0203ca74((void *)(owner + 0xa0), (Vec3 *)(owner + 0xbc));
        }
    } else if (msg[2] == 5) {
        switch (msg[3]) {
        case 0:
            spawn.bytes[3] = msg[5];
            spawn.bytes[2] = msg[6];
            spawn.bytes[1] = msg[7];
            translation.x = spawn.words[0] >> 8;
            spawn.bytes[7] = msg[8];
            spawn.bytes[6] = msg[9];
            spawn.bytes[5] = msg[0xa];
            translation.y = spawn.words[1] >> 8;
            spawn.bytes[11] = msg[0xb];
            spawn.bytes[10] = msg[0xc];
            spawn.bytes[9] = msg[0xd];
            translation.z = spawn.words[2] >> 8;
            func_0203c960(&transform);
            func_0203ca30(&transform, &translation);
            *(int *)(owner + msg[3] * 8 + 0x39c) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x398), 0x17, 0, &transform);
            break;
        case 2:
            ring.bytes[3] = msg[0x14];
            ring.bytes[2] = msg[0x15];
            ring.bytes[1] = msg[0x16];
            translation.x = ring.words[0] >> 8;
            ring.bytes[7] = msg[0x17];
            ring.bytes[6] = msg[0x18];
            ring.bytes[5] = msg[0x19];
            translation.y = ring.words[1] >> 8;
            ring.bytes[11] = msg[0x1a];
            ring.bytes[10] = msg[0x1b];
            ring.bytes[9] = msg[0x1c];
            translation.z = ring.words[2] >> 8;
            func_ov223_020d4e70(*(int **)(owner + 0x390), &translation, (const Quat *)(msg + 4));
            break;
        }
    }
    func_ov107_020c7500(owner, msg, arg);
}
