/* Message handler of the ov256 actor: a "spawned" message (kind 5) attaches an effect by its sub-kind
 * (byte 3) into the +0x46c / +0x470 slot pair under the +0x3c owner: 14 at the message's own spot
 * (mode 0xf), 0, 2, 4-7 and 9 likewise (mode 7), 8 spawns a shard at the packed 24-bit position in
 * bytes 5..13 (020d0c8c with the +0x4ac model, into +0x4b0), 10 / 12 on the +0x434 claw and 11 / 13 on
 * the +0x438 claw, 1 and 15 on the actor's +0xa0 node (byte 4 as the variant). The base handler always
 * runs. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c08cc(int model, int parent, int kind, int zero, int scale, void *spot);
extern int func_ov107_020c09a0(int model, int parent, int kind, void *at, int a, int b);
extern int func_ov256_020d0c8c(int owner, int model, Vec3 *pos);
extern void func_ov107_020c7500(int owner, unsigned char *command, int arg);

void func_ov256_020cc738(int owner, unsigned char *command, int arg)
{
    Vec3 pos;
    union {
        int words[3];
        unsigned char bytes[12];
    } packed;

    if (command[2] == 5) {
        switch (command[3]) {
        case 14:
            *(int *)(owner + command[3] * 8 + 0x470) = func_ov107_020c08cc(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x46c), 0xf, 0, 0x1000, command + 5);
            break;
        case 0:
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 9:
            *(int *)(owner + command[3] * 8 + 0x470) = func_ov107_020c08cc(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x46c), 7, 0, 0x1000, command + 5);
            break;
        case 8:
            packed.bytes[3] = command[5];
            packed.bytes[2] = command[6];
            packed.bytes[1] = command[7];
            pos.x = packed.words[0] >> 8;
            packed.bytes[7] = command[8];
            packed.bytes[6] = command[9];
            packed.bytes[5] = command[0xa];
            pos.y = packed.words[1] >> 8;
            packed.bytes[11] = command[0xb];
            packed.bytes[10] = command[0xc];
            packed.bytes[9] = command[0xd];
            pos.z = packed.words[2] >> 8;
            *(int *)(owner + 0x4b0) = func_ov256_020d0c8c(owner, *(int *)(owner + 0x4ac), &pos);
            break;
        case 10:
        case 12:
            *(int *)(owner + command[3] * 8 + 0x470) = func_ov107_020c09a0(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x46c), 7, (void *)(*(int *)(owner + 0x434) + 0xa0), command[4], 0);
            break;
        case 11:
        case 13:
            *(int *)(owner + command[3] * 8 + 0x470) = func_ov107_020c09a0(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x46c), 7, (void *)(*(int *)(owner + 0x438) + 0xa0), command[4], 0);
            break;
        case 1:
        case 15:
            *(int *)(owner + command[3] * 8 + 0x470) = func_ov107_020c09a0(*(int *)(owner + 0x3c),
                *(int *)(owner + command[3] * 8 + 0x46c), 7, (void *)(owner + 0xa0), command[4], 0);
            break;
        }
    }
    func_ov107_020c7500(owner, command, arg);
}
