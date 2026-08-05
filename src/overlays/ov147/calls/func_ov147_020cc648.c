typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero,
                               SrtTransform *transform);
extern int func_ov107_020cb040(int owner, int resourceId, int kind, int zero,
                               void *work);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov147_020cc648(int owner, unsigned char *command, int arg)
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

        switch (command[3]) {
        case 0:
            func_0203c960(&transform);
            func_0203ca30(&transform, &translation);
            *(int *)(owner + command[3] * 8 + 0x3f4) =
                func_ov107_020c0794(*(int *)(owner + 0x3c),
                                    *(int *)(owner + command[3] * 8 + 0x3f0),
                                    0x17, 0, &transform);
            break;
        case 2:
            *(int *)(owner + 0x3ec) =
                func_ov107_020cb040(owner, 0x126, 4, 0,
                                    (void *)(owner + 0xa0));
            break;
        }
    }

    func_ov107_020c7500(owner, command, arg);
}

