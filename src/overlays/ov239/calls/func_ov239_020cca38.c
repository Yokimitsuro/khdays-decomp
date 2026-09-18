/* Target distance of the ov239 enemy: acquires the actor's +0x394 target when missing (none
 * requests sub-state 2 and returns -1), aims the +0x10 yaw from the +0xb0 position at the
 * target's +0x190 point and returns the flat distance. */
typedef struct { int x, y, z; } VecFx32;

extern int func_ov107_020cab14(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int func_01ff8d18(VecFx32 *v, VecFx32 *d);
extern int func_020050b4(int x, int z);

int func_ov239_020cca38(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int len;

    if (*(int *)(*state + 0x394) == 0) {
        *(int *)(*state + 0x394) = func_ov107_020cab14(*state, 0);
        if (*(int *)(*state + 0x394) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
            return -1;
        }
    }
    VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x190), (void *)(*state + 0xb0), &d);
    d.y = 0;
    len = func_01ff8d18(&d, &d);
    state[4] = func_020050b4(d.x, d.z);
    return len;
}
