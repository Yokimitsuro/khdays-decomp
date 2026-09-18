/* Message handler of the ov134 enemy (x3: ov134/135/136), ported from the matched ov191 sibling. A
 * "spawned" message (kind 5): sub 0 attaches the +0x3a4 set's entry 0 to a transform built from
 * the message's packed position, the actor's +0xa0 quaternion and a unit scale (mode 0x15); sub 1
 * starts entry 2 from the payload (mode 0x15, weight 0xb33); sub 2 fixes entry 4 to the +0x394
 * item's +4 placement (mode 1). The base handler always runs. */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203c9d0(SrtTransform *transform, void *placement);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern int func_ov107_020c08cc(int model, int parent, int kind, int zero, int weight, void *payload);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov134_020cc2c4(int owner, unsigned char *command, int arg)
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
            func_0203c9d0(&transform, (void *)(owner + 0xa0));
            func_0203ca9c(&transform, 0x1000);
            (*(int **)(owner + 0x3a4))[1] = func_ov107_020c0794(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a4))[0], 0x15, 0, &transform);
            break;
        case 1:
            (*(int **)(owner + 0x3a4))[3] = func_ov107_020c08cc(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a4))[2], 0x15, 0, 0xb33, command + 5);
            break;
        case 2:
            (*(int **)(owner + 0x3a4))[5] = func_ov107_020c09a0(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a4))[4], 1, (void *)(*(int *)(owner + 0x394) + 4), 0, 1);
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
