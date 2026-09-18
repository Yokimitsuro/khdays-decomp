/* Message handler of the ov166 enemy (x3: ov166/167/168). A "spawned" message (kind 5) carries
 * a packed 24-bit position in bytes 5..13 which becomes the translation of a fresh transform;
 * the sub-kind then attaches the effect models of the +0x39c set: sub 0 fixes entry 0 to the
 * +0x390 item's +4 placement (mode 7), subs 1 and 2 start entries 4 and 2 from the transform;
 * sub 8 registers effect 0x114 (kind 7 or 8 by the message's +4 slot) or effect 0x13e (kind 4)
 * on the +0xa0 node into the +0x3a0 slot. The base handler always runs. */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern int func_ov107_020cb040(int owner, int resourceId, int kind, int zero, void *work);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov168_020d3c58(int owner, unsigned char *command, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        unsigned char bytes[12];
    } packed;

    if (command[2] == 5) {
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
        switch (command[3]) {
        case 0:
            (*(int **)(owner + 0x39c))[1] = func_ov107_020c09a0(*(int *)(owner + 0x3c), (*(int **)(owner + 0x39c))[0], 7, (void *)(*(int *)(owner + 0x390) + 4), 0, 0);
            break;
        case 1:
            (*(int **)(owner + 0x39c))[5] = func_ov107_020c0794(*(int *)(owner + 0x3c), (*(int **)(owner + 0x39c))[4], 7, 0, &transform);
            break;
        case 2:
            (*(int **)(owner + 0x39c))[3] = func_ov107_020c0794(*(int *)(owner + 0x3c), (*(int **)(owner + 0x39c))[2], 7, 0, &transform);
            break;
        case 8:
            switch (command[4]) {
            case 0:
                *(int *)(owner + command[4] * 4 + 0x3a0) = func_ov107_020cb040(owner, 0x114, 7, 0, (void *)(owner + 0xa0));
                break;
            case 1:
                *(int *)(owner + command[4] * 4 + 0x3a0) = func_ov107_020cb040(owner, 0x114, 8, 0, (void *)(owner + 0xa0));
                break;
            case 2:
                *(int *)(owner + command[4] * 4 + 0x3a0) = func_ov107_020cb040(owner, 0x13e, 4, 0, (void *)(owner + 0xa0));
                break;
            }
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
