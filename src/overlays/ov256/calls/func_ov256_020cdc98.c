/* Walk tick of the ov256 actor: it re-picks its target (020ccd54), the +0x44 heading turns by 35
 * degrees in the +0x70 direction, the +0x10 velocity is the +0x450 owner's +0x2c vector turned by its
 * heading (020cd054) scaled by 1 + boost/8 (+0x45c). Each time the partner holds no queued move (or on
 * the second +0x17a flag, or in retreat mode 4) the +0x4c step clock grows. Once the step count +0x54
 * reaches 5-7, or on those conditions, the walk winds down by stance (+0x69): 0 ends with the +0x74
 * mode + 2, 1 turns into stance 2 with pose 4 / motion 2, 2 ends once the partner is idle. Otherwise
 * every two steps the count grows and the stance flips; the stance picks pose 1 / motion 0 or pose 3 /
 * motion 2. Codegen: the stance flip is `(u8)(++stance) % 2`; `(u8)(stance + 1) % 2` adds in place
 * instead of into the ROM's fresh r3. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern int func_ov256_020ccd54(int *node);
extern void func_ov256_020cd054(int *out, int param_2, int *vec);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_02023eb4(int n);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov256_020cdc98(int *node)
{
    int *state = (int *)node[1];
    Vec3 v;

    func_ov256_020ccd54(node);
    state[0x11] += *((signed char *)state + 0x70) * 0x1922;
    func_ov256_020cd054((int *)&v, (int)node, (int *)(*(int *)(*state + 0x450) + 0x2c));
    {
        Vec3 *vel = (Vec3 *)(state + 4);

        *vel = v;
        func_01ffa724((*(int *)(*state + 0x45c) << 9) + 0x1000, vel, vel);
    }
    if (*(u8 *)(state[1] + 0xad) != 0 && !((struct Flag17a *)(*state + 0x17a))->b1 &&
        *((u8 *)state + 0x6b) != 4) {
        return;
    }
    state[0x13]++;
    if ((unsigned int)state[0x15] >= (unsigned int)(func_02023eb4(3) + 5) ||
        ((struct Flag17a *)(*state + 0x17a))->b1 || *((u8 *)state + 0x6b) == 4) {
        if (*((u8 *)state + 0x69) != 0) {
            if (*((u8 *)state + 0x69) == 1) {
                *((u8 *)state + 0x69) = 2;
                func_ov107_020c9264(*state, 4, 0);
                func_ov107_020c9ee8(*(int *)(*state + 0x450), 2, 0);
            } else if (*((u8 *)state + 0x69) == 2 && *(u8 *)(state[1] + 0xad) == 0) {
                *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
                func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            }
        } else {
            *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        }
        return;
    }
    if (state[0x13] >= 2) {
        state[0x13] = 0;
        state[0x15]++;
        *((u8 *)state + 0x69) = (u8)(++*((u8 *)state + 0x69)) % 2;
        if (*((u8 *)state + 0x69) == 0) {
            func_ov107_020c9264(*state, 1, 0);
            func_ov107_020c9ee8(*(int *)(*state + 0x450), 0, 0);
        } else {
            func_ov107_020c9264(*state, 3, 0);
            func_ov107_020c9ee8(*(int *)(*state + 0x450), 2, 0);
        }
        return;
    }
    if (*((u8 *)state + 0x69) == 0) {
        func_ov107_020c9264(*state, 1, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 0, 0);
    } else {
        func_ov107_020c9264(*state, 3, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 2, 0);
    }
}
