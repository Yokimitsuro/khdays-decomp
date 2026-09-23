/* Launch the first idle one of the ov283 actor's 16 helpers (+0x3a4, idle while its +0x388 is clear):
 * it starts (020cf1c0) at the +0x394 model's +0x14 point heading along +0x38, effects 4 and 5 play
 * there and the +0x54 launch count advances; below 16 the launch sound (0x173 variant 4) plays at the
 * +8 point and 1 is returned, the 16th wraps the count and returns 0 (as does finding no idle helper). */
typedef struct { int x, y, z; } Vec3;
struct Ov283Helpers { char pad[0x3a4]; int helpers[16]; };

extern void func_ov283_020cf1c0(int helper, Vec3 *pos, Vec3 *dir);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov283_020cc92c(int owner, int id, int mode, int at);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int func_ov283_020cc9e0(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    Vec3 dir;
    int i;

    for (i = 0; i < 0x10; i++) {
        if (*(int *)(((struct Ov283Helpers *)*state)->helpers[i] + 0x388) == 0) {
            pos = *(Vec3 *)(*(int *)(*state + 0x394) + 0x14);
            {
                int idx = ANG2IDX(state[0xe]) * 2;

                dir.x = data_0203d210[idx];
                dir.y = 0;
                dir.z = data_0203d210[idx + 1];
            }
            func_ov283_020cf1c0(((struct Ov283Helpers *)*state)->helpers[i], &pos, &dir);
            func_ov107_020c0b90(*state, 4, pos, 0);
            func_ov107_020c0b90(*state, 5, pos, 0);
            if (++state[0x15] >= 0x10) {
                state[0x15] = 0;
                return 0;
            }
            func_ov283_020cc92c(*state, 0x173, 4, state[2]);
            return 1;
        }
    }
    return 0;
}
