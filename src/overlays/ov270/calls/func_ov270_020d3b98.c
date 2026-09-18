/* Message handler of the ov269 enemy (and its byte-identical twins). A "spawned" message (kind 5): sub 0
 * decodes the packed 24-bit position in bytes 5..13 into a fresh transform, scales it by 2.0,
 * rotates it about the world Y axis by the packet's +0x10 angle and starts the first model of
 * the +0x3d4 set from it (mode 0x15); sub 1 starts the second from the payload at weight 0x1c8e;
 * sub 2 attaches the third (mode 1) to the actor's +0x3a4 placement (0, 1). The base handler always
 * runs. (020c08cc takes six arguments -- see func_ov120_020cc2a4; the packed bytes are
 * assembled through a byte-addressed union as in func_ov178_020cc3e0.) */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern void func_0203c9b4(SrtTransform *transform, const Vec3 *axis, int angle);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern int func_ov107_020c08cc(int model, int parent, int kind, int zero, int weight, void *payload);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);
extern const Vec3 data_02042264;

void func_ov270_020d3b98(int owner, unsigned char *command, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        unsigned char bytes[12];
    } packed;

    if (command[2] == 5) {
        switch (command[3]) {
        case 0:
            func_0203c960(&transform);
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
            func_0203ca30(&transform, &translation);
            func_0203ca9c(&transform, 0x2000);
            func_0203c9b4(&transform, &data_02042264, *(int *)(command + 0x10));
            (*(int **)(owner + 0x3d4))[1] = func_ov107_020c0794(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3d4))[0], 0x15, 0, &transform);
            break;
        case 1:
            (*(int **)(owner + 0x3d4))[3] = func_ov107_020c08cc(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3d4))[2], 0x15, 0, 0x1c8e, command + 5);
            break;
        case 2:
            (*(int **)(owner + 0x3d4))[5] = func_ov107_020c09a0(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3d4))[4], 1, (void *)(owner + 0x3a4), 0, 1);
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
