/* Update of the ov252 actor: the +0x54 heading turns towards +0x58 at the move's +0x7c rate (0x88
 * in move 2, 0xaa in move 4, 0x400 in move 5) and orients the +0xa0 pose. Without a rider (+0x78)
 * the +0x70 bob oscillates between 0 and 1.0 (+0xc0 direction) and, unless countering (+0xac) or in
 * moves 5, 7, 0xa or a mode-5 retreat, the +0x10 climb eases towards height 6.5 (half the
 * difference, +-1/16 per tick). The velocity goes to +0xf0 and x / z decay by 0.984. In move 4 the
 * +0x5c charge drains (ten times faster with the +0x4ec plate shown). The camera's +0x74 handler
 * gets the +0x55c part's point; the +0x78 rider timer frees the +0x6cc partner (bit 1 of +0x5c) when
 * it runs out; a queued pose change (+0xb0) plays poses 0x31 / 0x35 once the item's +0xaf byte
 * clears. In move 4 (not retreating) every 0x3800 of the +0x74 timer a shot is aimed 1.8 behind the
 * far +0x4e4 target (020cdfe8 > 32.0) along its facing, else 11.0 along the aim towards the +0x538
 * part; when that point lies on ground 3.5 below 32.0 the actor is knocked back there (mode 0x27).
 * Codegen: compiled with opt_dead_assignments off (push/pop scoped) and the products through the FX_Mul
 * inline; either one alone leaves the climb's difference and low word in swapped registers. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;
typedef struct { unsigned f : 8; } B8;
typedef struct { void *a; void *b; void *c; int d; } CollisionHit;

extern int func_0203d040(int a, int b, int c, int d);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern void func_0203c9d0(int a, void *b);
extern int OS_IsThreadAvailable_0x020c9848();
extern int func_ov022_02083f0c(void);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern int func_ov252_020cdfe8(int *node, Vec3 *to, int b);
extern int func_020050b4(int x, int y);
extern void func_ov252_020cdafc(Vec3 *v, int angle, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern CollisionHit *func_01fff920(void *collision, Vec3 *origin, Vec3 *direction);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern const Vec3 data_02042264;
extern const Vec3 data_ov252_020d43c8;
extern const Vec3 data_ov252_020d43b0;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

#pragma push
#pragma opt_dead_assignments off
void func_ov252_020cec2c(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    int plated;
    int item;
    int obj;
    int depth;
    int diff;
    CollisionHit *hit;

    plated = ((B8 *)(*(int *)(*state + 0x4ec) + 8))->f & 1;
    switch (*(signed char *)(*state + 0x100 + 0xc6)) {
    case 2:
        state[0x1f] = 0x88;
        break;
    case 4:
        state[0x1f] = 0xaa;
        break;
    case 5:
        state[0x1f] = 0x400;
        break;
    }
    state[0x15] = func_0203d040(state[0x15], state[0x16], state[0x1f], 0);
    func_0202f188(&q, &data_02042264, state[0x15]);
    func_0203c9d0(*state + 0xa0, &q);
    if (state[0x1e] == 0) {
        if (state[0x30] == 0) {
            state[0x1c] += 8;
            if (state[0x1c] >= 0x1000) {
                state[0x1c] = 0x1000;
                state[0x30] = 1;
            }
        } else {
            state[0x1c] -= 8;
            if (state[0x1c] <= 0) {
                state[0x1c] = 0;
                state[0x30] = 0;
            }
        }
        if (state[0x2b] == 0 &&
            *(signed char *)(*state + 0x100 + 0xc6) != 5 && *(signed char *)(*state + 0x100 + 0xc6) != 7 &&
            !(*(signed char *)(*state + 0x100 + 0xc6) == 4 && *(u8 *)(*state + 0x579) == 5) &&
            *(signed char *)(*state + 0x100 + 0xc6) != 0xa) {
            state[4] = FX_Mul(0x6800 - *(int *)(state[2] + 4), 0x800);
            state[4] = state[4] > 0x100 ? 0x100 : (state[4] < -0x100 ? -0x100 : state[4]);
        }
    }
    *(Vec3 *)(*state + 0xf0) = *(Vec3 *)(state + 3);
    state[3] = FX_Mul(state[3], 0xfc0);
    state[5] = FX_Mul(state[5], 0xfc0);
    if (*(signed char *)(*state + 0x100 + 0xc6) == 4) {
        if (!plated) {
            state[0x17] -= *(int *)(node[0] + 0x2c);
        } else {
            state[0x17] -= *(int *)(node[0] + 0x2c) * 10;
        }
        if (state[0x17] <= 0) {
            state[0x17] = 0;
        }
    }
    if (*(int *)(OS_IsThreadAvailable_0x020c9848() + 0x74) != 0) {
        obj = OS_IsThreadAvailable_0x020c9848();
        (*(void (**)(int, int, int))(obj + 0x74))(func_ov022_02083f0c(), 9, *(int *)(*state + 0x55c) + 0x14);
    }
    if (state[0x1e] != 0) {
        state[0x1e] -= *(int *)(node[0] + 0x2c);
        if (state[0x1e] <= 0) {
            *(int *)(*(int *)(*state + 0x6cc) + 0x5c) |= 2;
            state[0x1e] = 0;
        }
    }
    if (state[0x2c] != 0 && *(u8 *)(state[1] + 0xaf) == 0) {
        state[0x2c] = 0;
        func_ov107_020c9264(*state, 0x31, 0);
        func_ov107_020c9264(*state, 0x35, 0);
    }
    if (*(signed char *)(*state + 0x100 + 0xc6) != 4) {
        return;
    }
    if (*(u8 *)(*state + 0x579) == 5) {
        return;
    }
    if (state[0x1d] > 0x3800) {
        state[0x1d] = 0;
        item = *(int *)(*state + 4);
        Vec3 ray = data_ov252_020d43c8;
        Vec3 toTarget;
        Vec3 aim = data_ov252_020d43b0;

        if (func_ov252_020cdfe8(node, &toTarget, 0) > 0x20000) {
            func_ov252_020cdafc(&aim, func_020050b4(*(int *)(*(int *)(*state + 0x4e4) + 0x19c),
                                                    *(int *)(*(int *)(*state + 0x4e4) + 0x1a4)), &aim);
            VEC_Add(&aim, (Vec3 *)(*(int *)(*state + 0x4e4) + 0x190), &aim);
        } else {
            func_01ffa724(0xb000, &toTarget, &aim);
            VEC_Add(&aim, (Vec3 *)(*(int *)(*state + 0x538) + 0x14), &aim);
        }
        toTarget.y = 0;
        aim.y = 0x20000;
        hit = func_01fff920(*(void **)(item + 0x7c), &aim, &ray);
        if (hit == 0) {
            return;
        }
        if (hit->c != 0) {
            return;
        }
        depth = (int)(((long long)hit->d * ray.y) >> 27);
        if (depth < 0) {
            depth = -depth;
        }
        diff = depth - aim.y;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff > 0x10) {
            return;
        }
        aim.y = 0x100;
        func_ov107_020c0b90(*state, 0x27, aim, 0);
        return;
    }
    state[0x1d] += *(int *)(node[0] + 0x2c);
}
#pragma pop
