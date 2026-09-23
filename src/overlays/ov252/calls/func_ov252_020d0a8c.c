/* Pick the landing spot of the ov252 actor: of the five arena points (data_ov252_020d43ec) the one
 * nearest to the +0x4e4 target's +0x190 position. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 v[5]; } Vec3x5;

extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *out);
extern const Vec3x5 data_ov252_020d43ec;

Vec3 func_ov252_020d0a8c(int *node)
{
    int *state = (int *)node[1];
    Vec3 d;
    Vec3x5 spots = data_ov252_020d43ec;
    int bestDist;
    u8 i;
    int best;
    int dist;

    for (i = 0; i < 5; i++) {
        VEC_Subtract((Vec3 *)(*(int *)(*state + 0x4e4) + 0x190), &spots.v[i], &d);
        dist = func_01ff8d18(&d, &d);
        if (i == 0) {
            best = i;
            bestDist = dist;
        } else if (dist < bestDist) {
            bestDist = dist;
            best = i;
        }
    }
    return spots.v[best];
}
