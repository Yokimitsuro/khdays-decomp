/* Barrage tick of the ov252 actor: +0x6c accumulates the frame rate and it faces the target
 * (020cdfe8 with the offset); unguarded it backs off under 10.0 and closes in beyond 64.0 at 0.3125.
 * +0x64 and +0x68 accumulate too. Every 20th shot (+0x60) with a volley running (+0x88) the volley
 * restarts: +0x89 cue, the +0x588 flag clears, the +0x64c muzzle model hides and the shot timer is
 * set back 1.0. Each 0.125 a shot fires: with a target the owner fires effect 0x13 from the +0x570
 * muzzle along the +0x54 heading (spread +/-0xd6, raised up to 0.16 over the aim height); the muzzle
 * shows while a volley runs, a cue fires effect 0x34 at the +0x560 point with +0x588 set, and the shot
 * counters advance. Once the partner holds no queued move it turns toward the origin (020cdb88) and,
 * after 10.0 (15.0 guarded), clears +0x588, plays pose 0x1c and moves on to 020d0220; else pose 0x1b. */
typedef struct { int x, y, z; } Vec3;

extern int func_ov252_020cdfe8(int *node, Vec3 *delta, int face);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov252_020cdb88(int *node, Vec3 *v, int angle, int wantAbs);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov252_020d0220(void);
extern const short data_0203d210[];
extern const Vec3 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov252_020cfea8(int *node)
{
    int *state = (int *)node[1];
    Vec3 delta;
    Vec3 muzzle;
    Vec3 aim;
    Vec3 dir;
    Vec3 d;
    Vec3 p;
    int gap;
    int spread;

    state[0x1b] += *(int *)(node[0] + 0x2c);
    gap = func_ov252_020cdfe8(node, &delta, 1);
    if (state[0x2b] == 0) {
        if (gap < 0xa000) {
            func_01ffa724(-0x500, &delta, (Vec3 *)(state + 3));
        }
        if (gap > 0x40000) {
            func_01ffa724(0x500, &delta, (Vec3 *)(state + 3));
        }
    }
    state[0x19] += *(int *)(node[0] + 0x2c);
    state[0x1a] += *(int *)(node[0] + 0x2c);
    if (state[0x18] % 20 == 0 && *((unsigned char *)state + 0x88) != 0) {
        *((unsigned char *)state + 0x88) = 0;
        *((unsigned char *)state + 0x89) = 1;
        *(int *)(*state + 0x588) = 0;
        *(int *)(*(int *)(*state + 0x64c) + 0x5c) |= 2;
        state[0x19] -= 0x1000;
    }
    if (state[0x19] >= 0x200) {
        muzzle = *(Vec3 *)(*(int *)(*state + 0x570) + 0x14);
        if (*(int *)(*state + 0x4e4) != 0) {
            VEC_Subtract((Vec3 *)(*(int *)(*state + 0x4e4) + 0x190), &muzzle, &aim);
            func_01ff8d18(&aim, &dir);
            spread = func_02023eb4(0x1ad) - 0xd6;
            {
                int idx = ANG2IDX(state[0x15] + spread) * 2;

                aim.y = 0;
                aim.x = data_0203d210[idx];
                aim.z = data_0203d210[idx + 1];
            }
            {
                int lift = func_02023eb4(0x281) + (spread - spread);

                aim.y = dir.y + lift;
            }
            func_ov107_020c0b90(*state, 0x13, aim, 0);
        }
        if (*((unsigned char *)state + 0x88) == 0) {
            *(int *)(*(int *)(*state + 0x64c) + 0x5c) &= ~2;
        }
        if (*((unsigned char *)state + 0x89) != 0) {
            *((unsigned char *)state + 0x89) = 0;
            *(int *)(*state + 0x588) = 1;
            func_ov107_020c0b90(*state, 0x34, *(Vec3 *)(*(int *)(*state + 0x560) + 0x14), 0);
        }
        *((unsigned char *)state + 0x88) += 1;
        state[0x18]++;
        state[0x19] = 0;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    p = *(Vec3 *)state[2];
    p.y = 0;
    VEC_Subtract(&data_02041dc8, &p, &d);
    func_01ff8d18(&d, &d);
    func_ov252_020cdb88(node, &d, state[0x15], 1);
    if ((state[0x2b] == 0 && state[0x1a] >= 0xa000) || (state[0x2b] != 0 && state[0x1a] >= 0xf000)) {
        *(int *)(*state + 0x588) = 0;
        func_ov107_020c9264(*state, 0x1c, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0220);
    } else {
        func_ov107_020c9264(*state, 0x1b, 0);
    }
}
