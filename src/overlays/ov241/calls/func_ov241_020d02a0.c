/* Target finder of the ov241 enemy (x3: ov241/242/243): from the actor's +0x3bc heading builds
 * the forward vector (sine/cosine table) and an origin 1.5 units behind the +0x74 position;
 * walks the world's +0xa8 actor list for live actors (bit 1 of +0x40, bit 0 of +0x60) within
 * 30.0 of height, keeping the closest by flattened distance that is either inside 1.5 or, up
 * to 15.0, whose flattened direction from the origin (world Z when degenerate) lies within
 * the 0xf74 cosine of the heading, and that func_ov241_020d01bc accepts with its position and
 * +0x80 radius. Returns the best actor or 0. */
typedef struct { int x, y, z; } Vec3;
struct flags40 { int bit0 : 1, bit1 : 1; };
struct hw60 { unsigned short lo : 8, hi : 8; };

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int *func_01fffd70(void *list);
extern int *func_01fffd8c(void *list);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern int func_ov241_020d01bc(int *state, Vec3 pos, int radius);
extern const short data_0203d210[];
extern const Vec3 data_02042258;

int func_ov241_020d02a0(int node)
{
    int *state = *(int **)(node + 4);
    int heading = *(int *)(*state + 0x3bc);
    int best = 0;
    int bestDist = 0x7fffffff;
    int dist;
    int actor;
    int owner = *(int *)(*state + 4);
    int idx;
    Vec3 fwd;
    Vec3 origin;
    Vec3 d;
    Vec3 pos;
    int *pNode;
    int dy;

    idx = (unsigned short)((0x28BE60DB9391LL * heading + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.x = data_0203d210[(idx >> 4) << 1];                                          /* FX_SinIdx */
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                    /* FX_CosIdx */
    fwd.y = 0;
    func_01ffa724(-0x1800, &fwd, &origin);
    VEC_Add(&origin, (Vec3 *)(*state + 0x74), &origin);
    pNode = func_01fffd70((void *)(owner + 0xa8));
    actor = pNode == 0 ? 0 : *pNode;
    while (actor != 0) {
        if (((struct flags40 *)(actor + 0x40))->bit1 && (((struct hw60 *)(actor + 0x60))->lo & 1) != 0) {
            pos = *(Vec3 *)(actor + 0x74);
            VEC_Subtract(&pos, (Vec3 *)(*state + 0x74), &d);
            dy = d.y;
            if (dy < 0) {
                dy = -dy;
            }
            if (dy <= 0x1e000) {
                d.y = 0;
                dist = func_01ff8d18(&d, &d);
                if (dist < bestDist) {
                    VEC_Subtract(&pos, &origin, &d);
                    d.y = 0;
                    if (func_01ff8d18(&d, &d) == 0) {
                        d = data_02042258;
                    }
                    if (dist <= 0x1800 || (dist <= 0xf000 && VEC_DotProduct(&d, &fwd) >= 0xf74)) {
                        if (func_ov241_020d01bc(state, pos, *(int *)(actor + 0x80)) != 0) {
                            bestDist = dist;
                            best = actor;
                        }
                    }
                }
            }
        }
        pNode = func_01fffd8c((void *)(owner + 0xa8));
        actor = pNode == 0 ? 0 : *pNode;
    }
    return best;
}
