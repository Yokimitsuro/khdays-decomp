/* Attack hit test of the ov237 actor: the targets touching `sphere` (else `box`, else `segment`) are
 * tried in turn; each first follows the +0x3d8-relative push (020cdb50) and, unless `once` already
 * marked it in the +0x57 mask, is pushed (020ca918, kind `kind`). The first target hit spawns effect
 * `effect` 1.25 above it, plays hit sound 0x12d (variant 5 for kind 0, 0xc for kinds 2 / 4) and
 * returns 1; 0 when nothing is hit. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;

extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern int func_ov107_020c8df0(int owner, void *box, int *hits);
extern int func_ov107_020c8f44(int owner, void *segment, int *hits);
extern Vec3 func_ov237_020cdb50(int *node, Vec3 *target);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);

int func_ov237_020cdbe4(int *node, void *sphere, void *box, void *segment, Vec3 *push, int once, u16 effect, u16 kind)
{
    int *state = (int *)node[1];
    int hits[4];
    Vec3 pos;
    long n;
    long i;
    u8 bit;

    if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    } else if (box != 0) {
        n = func_ov107_020c8df0(*state, box, hits);
    } else {
        n = func_ov107_020c8f44(*state, segment, hits);
    }
    for (i = 0; i < n; i++) {
        bit = 1 << *(u16 *)(hits[i] + 2);
        *push = func_ov237_020cdb50(node, push);
        if (once != 0 && (*((u8 *)state + 0x57) & bit)) {
            continue;
        }
        if (func_ov107_020ca918(hits[i], *state, *state, kind, push, 0) == 0) {
            continue;
        }
        pos = *(Vec3 *)(hits[i] + 0x190);
        pos.y += 0x1400;
        if (once != 0) {
            *((u8 *)state + 0x57) |= bit;
        }
        func_ov107_020c0b90(*state, effect, pos, 0);
        switch (kind) {
        case 0:
            func_ov107_020c5af8(*state, 0x12d, 5, state[0xe]);
            break;
        case 2:
        case 4:
            func_ov107_020c5af8(*state, 0x12d, 0xc, state[0xe]);
            break;
        }
        return 1;
    }
    return 0;
}
