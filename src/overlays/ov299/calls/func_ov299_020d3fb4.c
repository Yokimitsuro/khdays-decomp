/* Message handler of the ov299 enemy. A "spawned" message (kind 5) carries a packed 24-bit
 * position in bytes 5..13 which becomes the translation of a fresh transform; sub-kinds 0/1/2
 * attach the matching +0x394 part model to it as the +0x398 effect (kind 0x15, or 0x17 for
 * parts 1/2) under the +0x3c owner, and part 1 spawning within 0xa000 of the player (the
 * manager's first actor +0x88) fires effect 1 on the actor. The base handler always runs. */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, unsigned char kind, int zero, SrtTransform *transform);
extern int *OS_IsThreadAvailable_0x020c9848(void);
extern void VEC_Subtract(const void *a, const Vec3 *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_ov107_020c0b14(int owner, int effect);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov299_020d3fb4(int owner, unsigned char *command, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    Vec3 d;
    union {
        int words[3];
        unsigned char bytes[12];
    } packed;
    int *manager;

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
        switch (command[3]) {
        case 0: case 1: case 2:
            *(int *)(owner + command[3] * 8 + 0x398) = func_ov107_020c0794(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x394), (command[3] != 0 ? 2 : 0) | 0x15, 0, &transform);
            if (command[3] == 1) {
                manager = OS_IsThreadAvailable_0x020c9848();
                if (manager != 0 && *manager != 0) {
                    VEC_Subtract((void *)(*manager + 0x88), &translation, &d);
                    if (func_01ff8d18(&d, &d) <= 0xa000) {
                        func_ov107_020c0b14(owner, 1);
                    }
                }
            }
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
