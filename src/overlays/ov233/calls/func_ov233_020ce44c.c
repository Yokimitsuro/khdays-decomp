/* Grab release of the ov276 enemy: with a +8 held actor and the +0x1c4 flags clear of bit 1,
 * the +0x40/+0x44 yaws face from the +0xc position to the held actor's +0x190 point and the
 * hold is dropped; animation 0xc plays, the overlay's animation 9 starts, effect 2 spawns at the
 * origin, reaction 0x164 mode 4 fires at the position, the +0x4c timer and +0x61 flag reset and
 * the tick hands off to d1d14. */
struct Vecx32 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, struct Vecx32 *d);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov233_020cd49c(int actor, int anim);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern void func_ov107_020c5af8(int actor, int a, int id, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov233_020ce524(int *node);
extern struct Vecx32 data_02041dc8;

void func_ov233_020ce44c(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 d;

    if (state[2] != 0 && (*(unsigned char *)((char *)state + 0x1c4) & 2) == 0) {
        VEC_Subtract((void *)(state[2] + 0x190), (void *)state[3], &d);
        state[0x10] = state[0x11] = func_020050b4(d.x, d.z);
        state[2] = 0;
    }
    func_ov107_020c9264(*state, 0xc, 0);
    func_ov233_020cd49c(*state, 9);
    func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
    func_ov107_020c5af8(*state, 0x164, 4, (void *)state[3]);
    state[0x13] = 0;
    *(unsigned char *)((char *)state + 0x61) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov233_020ce524);
}
