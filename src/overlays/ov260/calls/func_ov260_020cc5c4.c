/* Message handler of the ov260 actor: a "spawned" message (kind 5) carries a packed 24-bit position
 * in bytes 5..13 which becomes the translation of a fresh transform; the sub-kind (message byte 3)
 * attaches an effect into its +0x478 / +0x47c slot pair (message byte 4 as the variant, +0x3c owner):
 * 0, 2-4, 6, 7 at the transform (mode 0x17; 9 also turned by the +0xa0 rotation, mode 0x1f), 2 and 6
 * also flag the actor (020c0b14); 1 and 8 on the +0x3e4 node (mode 0x1f, 8 looped); 5 and 0xa on the
 * +0x3b8 node; 0xb on the +0x424 part; 0xd releases the effect in slot byte 4. The base handler
 * always runs. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203c9d0(SrtTransform *transform, void *quat);
extern int func_ov107_020c0794(int model, int parent, int kind, int variant, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern void func_ov107_020c0b14(int owner, int flag);
extern void func_0203c650(void *taskList, void *handle);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov260_020cc5c4(int owner, unsigned char *command, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        unsigned char bytes[12];
    } packed;

    if (command[2] == 5) {
        u8 kind = 0x17;

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
        case 9:
            kind |= 8;
            func_0203c9d0(&transform, (void *)(owner + 0xa0));
            /* fall through */
        case 0:
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
            *(int *)(owner + command[3] * 8 + 0x47c) = func_ov107_020c0794(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x478), kind, command[4], &transform);
            if (!(command[3] != 2 && command[3] != 6)) {
                func_ov107_020c0b14(owner, 1);
            }
            break;
        case 1:
        case 8:
            *(int *)(owner + command[3] * 8 + 0x47c) = func_ov107_020c09a0(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x478), 0x1f, (void *)(owner + 0x3e4), command[4],
                command[3] == 8);
            break;
        case 5:
        case 0xa:
            *(int *)(owner + command[3] * 8 + 0x47c) = func_ov107_020c09a0(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x478), kind, (void *)(owner + 0x3b8), command[4], 0);
            break;
        case 0xb:
            *(int *)(owner + command[3] * 8 + 0x47c) = func_ov107_020c09a0(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x478), kind, (void *)(*(int *)(owner + 0x424) + 4),
                command[4], 0);
            break;
        case 0xd:
            if (*(void **)(owner + command[4] * 8 + 0x47c) != 0) {
                func_0203c650(*(void **)(owner + 0x3c), *(void **)(owner + command[4] * 8 + 0x47c));
                *(void **)(owner + command[4] * 8 + 0x47c) = 0;
            }
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
