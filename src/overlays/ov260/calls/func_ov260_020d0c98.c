/* Message handler of the ov260 actor: a "spawned" message (kind 5) carries a packed 24-bit position
 * in bytes 5..13 which becomes the translation of a fresh transform; sub-kinds 0 and 1 attach the
 * effect model of their +0x394 slot there (mode 0x17 under the +0x3c owner, message byte 4 as the
 * variant) into the slot's +0x398 handle. The base handler always runs. */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int variant, SrtTransform *transform);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov260_020d0c98(int owner, unsigned char *command, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        unsigned char bytes[12];
    } packed;

    if (command[2] == 5) {
        packed.bytes[3] = command[5];
        packed.bytes[2] = command[6];
        packed.bytes[1] = command[7];
        translation.x = packed.words[0] >> 8;
        packed.bytes[7] = command[8];
        packed.bytes[6] = command[9];
        packed.bytes[5] = command[0xa];
        translation.y = packed.words[1] >> 8;
        packed.bytes[11] = command[0xb];
        packed.bytes[10] = command[0xc];
        packed.bytes[9] = command[0xd];
        translation.z = packed.words[2] >> 8;
        func_0203c960(&transform);
        func_0203ca30(&transform, &translation);
        if (!(command[3] != 0 && command[3] != 1)) {
            *(int *)(owner + command[3] * 8 + 0x398) = func_ov107_020c0794(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x394), 0x17, command[4], &transform);
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
