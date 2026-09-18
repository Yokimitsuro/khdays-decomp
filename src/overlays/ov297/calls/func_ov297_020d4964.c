/* Wander tick of the ov297 enemy. The +0x3c clock accumulates the frame-time and the +0x54 timer
 * counts it down; with the target within 0x4b00 (beyond both +0x80 radii) the +0x5c chase clock
 * grows and, past 0x2fd0, sub-state 7 is requested and the state ends. Mode +0x90 0: beyond
 * 0x9000 the +0x84 alert clears, sub-state 2 is requested and the state ends; else the alert is
 * set, the +0x2c/+0x30 yaws advance by the +0x28 turn and the wander step runs; a wall contact
 * with the +0x44 timer spent rolls a new turn (0x1922 to 0x3243), counts +0x78 (arming +0x58 at
 * 0x1fe0 after two) and, with a 15% roll, aims the yaws at the target and requests sub-state 5.
 * Mode 1: a spent +0x54 timer advances the yaws and re-arms it at 0x1fe0; the target is
 * re-acquired (none requests sub-state 2) and the gap decides between the wander step (alert)
 * and sub-state 2 (beyond 0x9000, alert cleared); a wall contact reflects the facing of the
 * +0x2c yaw about the contact normal (half the time after a new turn), redirects the +0x10
 * velocity, counts +0x78 (sub-state 2 after two), re-arming the timer at 0xff0. The clock then
 * plays the held-item animations 0 (from 0x4c8) and 1 (from 0x908, resetting the clock and the
 * +0x93 marks); animation 1 plays while the +4 item's +0xad byte is clear. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
struct Bits17a { u8 bit0 : 1, bit1 : 1; };

extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov297_020d4168(int *node);
extern void func_ov297_020d4240(int *node);
extern unsigned int func_02023e80(unsigned int range);
extern int func_02023eb4(int range);
extern int func_020050b4(int x, int z);
extern int func_ov107_020cab14(int actor, int mode);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov297_020d406c(int actor, int anim);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void func_ov297_020d4964(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3 dir;
    Vec3 n;
    Vec3 back;
    Vec3 refl;
    int gap;
    int len;
    int turn;
    int actor;
    unsigned int idx;

    state[0xf] += *(int *)(*node + 0x2c);
    state[0x15] -= *(int *)(*node + 0x2c);
    VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x190), (void *)(*state + 0xb0), &d);
    len = func_01ff8d18(&d, &d);
    actor = *state;
    if (len - (*(int *)(*(int *)(actor + 0x394) + 0x80) + *(int *)(actor + 0x80)) < 0x4b00) {
        state[0x17] += *(int *)(*node + 0x2c);
        if (state[0x17] >= 0x2fd0) {
            *(u8 *)(*state + 0x1c7) = 7;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    switch (*(signed char *)(state + 0x24)) {
    case 0:
        if (func_ov297_020d4168(node) < 0x9000) {
            state[0x21] = 1;
            state[0xd] = state[0xc] = state[0xc] + state[10];
            func_ov297_020d4240(node);
        } else {
            state[0x21] = 0;
            *(u8 *)(*state + 0x1c7) = 2;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0 && state[0x11] <= 0) {
            state[10] = func_02023e80(0x1922) + 0x1922;
            state[0x1e]++;
            if (state[0x1e] > 2) {
                state[0x16] = 0x1fe0;
            }
            if ((unsigned int)func_02023eb4(0x64) < 0xf) {
                VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x74), (void *)(*state + 0x74), &dir);
                func_01ff8d18(&dir, &dir);
                state[0xb] = state[0xc] = func_020050b4(dir.x, dir.z);
                *(u8 *)(*state + 0x1c7) = 5;
            }
        }
        break;
    case 1:
        if (state[0x15] <= 0) {
            func_ov297_020d4168(node);
            state[0xd] = state[0xc] = state[0xc] + state[10];
            state[0x15] = 0x1fe0;
        }
        *(int *)(*state + 0x394) = func_ov107_020cab14(*state, 0);
        if (*(int *)(*state + 0x394) == 0) {
            *(u8 *)(*state + 0x1c7) = 2;
        }
        VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x190), (void *)(*state + 0xb0), &d);
        len = func_01ff8d18(&d, &d);
        actor = *state;
        gap = len - (*(int *)(*(int *)(actor + 0x394) + 0x80) + *(int *)(actor + 0x80));
        if (gap < 0) {
            gap = 0;
        }
        if (gap < 0x9000) {
            state[0x21] = 1;
            func_ov297_020d4240(node);
        } else {
            state[0x21] = 0;
            *(u8 *)(*state + 0x1c7) = 2;
        }
        if (((struct Bits17a *)(*state + 0x17a))->bit1 != 0) {
            n = *(Vec3 *)(*state + 0x114);
            if ((unsigned int)func_02023eb4(0x64) < 0x32) {
                turn = func_02023e80(0x1922) + 0x1922;
                state[10] = turn;
                state[0xd] = state[0xc] = state[0xc] + turn;
            }
            idx = ANG2IDX(state[0xb]);
            back.x = -data_0203d210[idx * 2];
            back.y = 0;
            back.z = -data_0203d210[idx * 2 + 1];
            func_01ffa724(VEC_DotProduct(&back, &n) << 1, &n, &refl);
            VEC_Subtract(&refl, &back, &refl);
            func_01ff8d18(&refl, &refl);
            state[0xd] = func_020050b4(refl.x, refl.z);
            len = func_01ff8d18((Vec3 *)(state + 4), (Vec3 *)(state + 4));
            func_01ffa724(len, &refl, (Vec3 *)(state + 4));
            state[0x1e]++;
            state[0x15] = 0xff0;
            if (state[0x1e] > 2) {
                *(u8 *)(*state + 0x1c7) = 2;
            }
        }
        break;
    }
    if ((*(u8 *)((char *)state + 0x93) & 1) == 0 && state[0xf] >= 0x4c8) {
        *(u8 *)((char *)state + 0x93) |= 1;
        func_ov297_020d406c(*state, 0);
    }
    if ((*(u8 *)((char *)state + 0x93) & 2) == 0 && state[0xf] >= 0x908) {
        *(u8 *)((char *)state + 0x93) |= 2;
        func_ov297_020d406c(*state, 1);
        state[0xf] = 0;
        *(u8 *)((char *)state + 0x93) = 0;
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 0);
    }
}
