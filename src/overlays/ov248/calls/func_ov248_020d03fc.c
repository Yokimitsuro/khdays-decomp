/* Message handler of the ov248 actor: a "spawned" message (kind 5) carries a packed 24-bit position in
 * bytes 5..13 which becomes the translation of a fresh transform; sub-kind 0 attaches slot 0's model
 * to it (mode 0x17, message +4), sub-kind 1 places slot 1's model on the +0xa0 node (message +4, flag
 * when it is 2); the effect lands in the slot's +4. The base handler always runs. */
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;
struct Slot { int model; int effect; };
struct Ov248Actor { char pad[0x388]; struct Slot slots[2]; };

extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov248_020d03fc(int owner, unsigned char *command, int arg)
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
            ((struct Ov248Actor *)owner)->slots[command[3]].effect =
                func_ov107_020c0794(*(int *)(owner + 0x3c), ((struct Ov248Actor *)owner)->slots[command[3]].model, 0x17, command[4], &transform);
            break;
        case 1:
            ((struct Ov248Actor *)owner)->slots[command[3]].effect =
                func_ov107_020c09a0(*(int *)(owner + 0x3c), ((struct Ov248Actor *)owner)->slots[command[3]].model, 0x17, (void *)(owner + 0xa0), command[4], command[4] == 2);
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
