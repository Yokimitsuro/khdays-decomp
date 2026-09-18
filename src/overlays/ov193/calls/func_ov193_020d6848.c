/* Shockwave tick of the ov191 enemy (x3: ov191/192/193): walks the owner's +0xa8 actor list and,
 * for every actor of the same team (+4) whose +0x74 position lies inside the state's box
 * (+0x28..+0x30 min, +0x34..+0x3c max), applies hit 0 with a 0x800 push along the normalised
 * direction from the state's +4 origin (flags 0x18). The +0x24 timer advances by the node's
 * +0x2c speed and at 0xa00 the sub-state drops to 0 with the slot cleared. */
typedef struct { int x, y, z; } Vec3;

extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int victim, int a, int b, int mode, Vec3 *push, int flags);
extern void func_0203c634(int node, int slot, void *cb);

void func_ov193_020d6848(int node)
{
    int *state = *(int **)(node + 4);
    int owner = *(int *)(*state + 4);
    int *pNode;
    int actor;
    Vec3 push;

    pNode = func_01fffd70((void *)(owner + 0xa8));
    actor = pNode == 0 ? 0 : *pNode;
    while (actor != 0) {
        if (*(int *)(actor + 4) == *(int *)(*state + 4)
            && *(int *)(actor + 0x74) >= state[10] && *(int *)(actor + 0x78) >= state[0xb]
            && *(int *)(actor + 0x7c) >= state[0xc]
            && *(int *)(actor + 0x74) <= state[0xd] && *(int *)(actor + 0x78) <= state[0xe]
            && *(int *)(actor + 0x7c) <= state[0xf]) {
            VEC_Subtract((Vec3 *)(actor + 0x74), (Vec3 *)state[1], &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            func_ov107_020ca918(actor, *state, *(int *)(*state + 0x38c), 0, &push, 0x18);
        }
        pNode = func_01fffd8c((void *)(owner + 0xa8));
        actor = pNode == 0 ? 0 : *pNode;
    }
    state[9] += *(int *)(*(int *)node + 0x2c);
    if (state[9] >= 0xa00) {
        *(unsigned char *)(*state + 0x1c7) = 0;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
