/* Gap between the ov259 actor and its +8 target: the distance from the actor's +0xb0 position to
 * the target's +0x190 point minus both +0x80 radii. Without a target the actor goes to move 2 and
 * the node ends (the result is then left undefined, as in the original). */
typedef struct { int x, y, z; } Vec3;

extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);

int func_ov259_020cdd48(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;

    if (state[2] == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        VEC_Subtract((Vec3 *)(state[2] + 0x190), (Vec3 *)(*state + 0xb0), &d);
        return func_01ff8d18(&d, &d) - (*(int *)(state[2] + 0x80) + *(int *)(*state + 0x80));
    }
}
