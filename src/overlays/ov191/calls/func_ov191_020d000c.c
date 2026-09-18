/* Message handler of the ov191 enemy (x3: ov191/192/193). A "spawned" message (kind 5): sub 0
 * attaches the first two models of the +0x3a0 set to the actor's +0x3ac placement (mode 0x17);
 * sub 1 starts the third from the packet payload at weight 0x1000; sub 2 decodes the packed
 * 24-bit position in bytes 5..13 into a fresh transform, concatenates the actor's +0xa0
 * placement and starts the fourth model from it. The base handler always runs.
 * 020c08cc takes six arguments (see func_ov120_020cc2a4); the set pointer is reloaded for each
 * store (see func_ov178_020cc3e0). */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203c9d0(SrtTransform *transform, void *placement);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern int func_ov107_020c08cc(int model, int parent, int kind, int zero, int weight, void *payload);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov191_020d000c(int owner, unsigned char *command, int arg)
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
            (*(int **)(owner + 0x3a0))[1] = func_ov107_020c09a0(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a0))[0], 0x17, (void *)(owner + 0x3ac), 0, 0);
            (*(int **)(owner + 0x3a0))[3] = func_ov107_020c09a0(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a0))[2], 0x17, (void *)(owner + 0x3ac), 0, 0);
            break;
        case 1:
            (*(int **)(owner + 0x3a0))[5] = func_ov107_020c08cc(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a0))[4], 0x17, 0, 0x1000, command + 5);
            break;
        case 2:
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
            (*(int **)(owner + 0x3a0))[7] = func_ov107_020c0794(*(int *)(owner + 0x3c), (*(int **)(owner + 0x3a0))[6], 0x17, 0, &transform);
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
