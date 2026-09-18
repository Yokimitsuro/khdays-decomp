/* Shot windup of the ov123 enemy (and its byte-identical twin): re-acquires the target into
 * +0x24 (none requests sub-state 2 and ends the state); the +0x28 timer accumulates the
 * frame-time and, once past 0xccc with the +0x2c flag clear, the direction from the +0x390
 * item's +0x14 point to the target's +0x74 is normalised, its height kept, the forward axis
 * rotated by the actor's +0xa0 orientation takes the flat part, the flag latches and the +0x394
 * shot is launched (cd484) along it. Once the +0x30 busy byte clears sub-state 2 is requested
 * and the state ends. */
typedef struct { int x, y, z; } Vec3;
extern int func_ov123_020cd224(int actor, int mode);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_0202f384(Vec3 *dst, void *quat, const Vec3 *src);
extern void func_ov123_020cd484(int shot, void *from, Vec3 *dir);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;

void func_ov123_020cceec(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int y;

    state[9] = func_ov123_020cd224(*state, 0);
    if (state[9] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[10] += *(int *)(*node + 0x2c);
    if (state[0xb] == 0 && state[10] >= 0xccc) {
        VEC_Subtract((void *)(state[9] + 0x74), (void *)(*(int *)(*state + 0x390) + 0x14), &dir);
        func_01ff8d18(&dir, &dir);
        y = dir.y;
        state[0xb] = 1;
        func_0202f384(&dir, (void *)(*state + 0xa0), &data_02042258);
        dir.y = y;
        func_01ff8d18(&dir, &dir);
        func_ov123_020cd484(*(int *)(*state + 0x394), (void *)(*(int *)(*state + 0x390) + 0x14), &dir);
    }
    if (*(unsigned char *)state[0xc] != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
