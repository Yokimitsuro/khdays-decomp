/* Warp tick of the ov256 actor: on the first tick (+0x4c clear) it is placed (020c5c54) 5.0 above
 * the +0x430 partner's +0x190 point, or, with a leash request (+0x78), 5.0 above a new perch
 * stored in +0x1c: one of five random spots (+0x7c) or the arena corner nearest to the +0xc
 * track. After 0x1a90 of the timer the +0x428 shape loses bit 1, pose 0x18 / partner motion 0xa
 * play, the actor is knocked back at the track (mode 6), +0x69 is set and the node moves on to
 * 020cec64. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 v[5]; } Spots5;
typedef struct { Vec3 v[4]; } Corners4;
typedef struct { unsigned f : 8; } B8;

extern int func_02023eb4(int n);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov256_020cec64(void);
extern const Spots5 data_ov256_020d2600;
extern const Corners4 data_ov256_020d25d0;

static inline void VecSet(Vec3 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void func_ov256_020cea18(int *node)
{
    int *state = (int *)node[1];
    Vec3 at;
    signed char i;
    int best;
    int bestDist;
    int dist;

    if (state[0x13] == 0) {
        VecSet(&at, *(int *)(*(int *)(*state + 0x430) + 0x190), *(int *)(*(int *)(*state + 0x430) + 0x194) + 0x5000,
               *(int *)(*(int *)(*state + 0x430) + 0x198));
        if (state[0x1e] != 0) {
            if (state[0x1f] != 0) {
                Spots5 spots = data_ov256_020d2600;

                at = spots.v[func_02023eb4(5)];
                *(Vec3 *)(state + 7) = at;
                at.y += 0x5000;
            } else {
                Corners4 corners = data_ov256_020d25d0;
                Vec3 d;

                for (i = 0; i < 4; i++) {
                    VEC_Subtract(&corners.v[i], (Vec3 *)state[3], &d);
                    dist = func_01ff8d18(&d, &d);
                    if (i != 0) {
                        if (bestDist > dist) {
                            best = i;
                            bestDist = dist;
                        }
                    } else {
                        best = 0;
                        bestDist = dist;
                    }
                }
                *(Vec3 *)(state + 7) = corners.v[best];
                at = *(Vec3 *)(state + 7);
                at.y += 0x5000;
            }
        }
        func_ov107_020c5c54(*state, &at);
    }
    state[0x13] += *(int *)(node[0] + 0x2c);
    if (!(state[0x13] < 0x1a90)) {
        ((B8 *)(*(int *)(*state + 0x428) + 8))->f &= ~2;
        func_ov107_020c9264(*state, 0x18, 0);
        func_ov107_020c9ee8(*(int *)(*state + 0x450), 0xa, 0);
        func_ov107_020c0b90(*state, 6, *(Vec3 *)state[3], 0);
        state[0x13] = 0;
        *((u8 *)state + 0x69) = 1;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov256_020cec64);
        return;
    }
}
