/* Knock-back reaction of the ov146 actor (unless +0x1ac bit 0 shields it): an attacker hitting it
 * outside move 1 launches it away along the attacker's heading (020ce694), pose 6 plays, +0x1c is set
 * and the next move is 1. Always returns 0. */
typedef struct { int x, y, z; } Vec3;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern void func_ov146_020ce694(int *state, Vec3 dir);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

int func_ov146_020ce6e4(char *self, char *attacker)
{
    int *state = *(int **)(self + 0x214);
    Vec3 d;
    Vec3 dir;

    if (*(unsigned short *)(self + 0x1ac) & 1) {
        return 0;
    }
    if (attacker != 0 && *(signed char *)(*state + 0x1c6) != 1) {
        VEC_Subtract((Vec3 *)(*state + 0xb0), (Vec3 *)(attacker + 0x190), &d);
        {
            int idx = ANG2IDX(func_020050b4(d.x, d.z)) * 2;

            dir.y = 0;
            dir.x = data_0203d210[idx];
            dir.z = data_0203d210[idx + 1];
        }
        func_ov146_020ce694(state, dir);
        func_ov107_020c9264(*state, 6, 0);
        state[7] = 1;
        *(unsigned char *)(*state + 0x1c7) = 1;
    }
    return 0;
}
