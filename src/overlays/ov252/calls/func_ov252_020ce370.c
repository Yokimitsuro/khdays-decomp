/* Guard sweep of the ov252 actor: while its +0x60 guard flag and the +0x98 guard are both up, the
 * guard sphere (its +0x530 model's +0x14 point, radius 8.0) is tested twice against kind-6 targets
 * (020ce0a8); each sweep that has hit anything so far plays sound 0/0x51 at the +8 point, and the
 * +0x85 hit mask keeps only the targets that were hit. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 center; int nRadius; } Sphere;
typedef struct { u16 lo : 8; u16 hi : 8; } flags16;

extern u8 func_ov252_020ce0a8(int *state, int kind, Sphere *sphere, void *cyl, void *box);
extern void func_ov107_020c5af8(int actor, int bank, int variant, void *at);

void func_ov252_020ce370(int *node)
{
    int *state = (int *)node[1];
    u8 i;
    u8 hit;
    Sphere guard;

    if ((((flags16 *)(*state + 0x60))->lo & 1) == 0 || state[0x26] == 0) {
        return;
    }
    hit = 0;
    for (i = 0; i < 2; i++) {
        guard.center = *(Vec3 *)(*(int *)(*state + 0x530) + 0x14);
        guard.nRadius = 0x8000;
        if ((hit |= func_ov252_020ce0a8(state, 6, &guard, 0, 0)) != 0) {
            func_ov107_020c5af8(*state, 0, 0x51, (void *)state[2]);
        }
    }
    *((u8 *)state + 0x85) &= hit;
}
