/* Approach tick of the ov178 enemy (x3: ov178/179/180): while no override height is pending
 * (+0x88), steer the hover height (+0x24) -- towards 0x2800 by a 1/30 step when the target
 * height (+0x44) is unset, otherwise 0x200 per tick towards the actor's +0x194; face the target
 * (look-at matrix from the actor's +0x74 to the target's +0x74, applied via 0202ea48), keep the
 * normalised direction from the actor's anchor (+0x390 +0x14), advance the +0x48 phase by the
 * node's +0x2c speed and, once the actor's +0xad flag is clear, run the setup (020ce710) and
 * hand over to sub-state 2 with the slot cleared. */
typedef struct { int x, y, z; } Vec3;

extern void func_0203cd7c(void *mtx, Vec3 *from, Vec3 *to, void *up);
extern void func_0202ea48(void *dst, void *mtx);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_ov178_020ce710(int rig, int target, Vec3 *dir);
extern void func_0203c634(int obj, int slot, void *cb);
extern int data_02042264;

void func_ov178_020ce220(int node)
{
    char *actor;
    int *state = *(int **)(node + 4);
    char mtx[0x24];
    Vec3 dir;

    actor = (char *)state[3];
    if (state[0x22] == 0) {
        if (state[0x11] != 0x7fffffff) {
            state[9] += (0x2800 - state[0x11]) / 30;
        } else if (*(int *)(actor + 0x194) < state[9]) {
            state[9] -= 0x200;
        } else {
            state[9] += 0x200;
        }
    }
    func_0203cd7c(mtx, (Vec3 *)(actor + 0x74), (Vec3 *)state[2], &data_02042264);
    func_0202ea48(state + 0x1d, mtx);
    VEC_Subtract((Vec3 *)(actor + 0x74), (Vec3 *)(*(int *)(*state + 0x390) + 0x14), &dir);
    func_01ff8d18(&dir, &dir);
    state[0x12] += *(int *)(*(int *)node + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) == 0) {
        func_ov178_020ce710(*(int *)(*state + 0x3ac), state[2], &dir);
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 0x20), 0);
    }
}
