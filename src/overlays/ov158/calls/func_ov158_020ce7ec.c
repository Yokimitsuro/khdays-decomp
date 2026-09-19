/* Ground drop tick of the ov158 enemy. In owner mode 1 the +0x28 radius grows by the owner's
 * rate and, up to 0xe00, the entities inside 2.2 times that radius around the +0x10 anchor are
 * swept: each one whose +0x1b4 slot bit is still clear in the +0x30 hit mask is tested along
 * the unit direction from the anchor (scaled 0x800) and, once accepted, fires reaction 0 mode
 * 0x53 at the anchor and marks its bit. The state ends once the +0xc sub-object goes idle
 * (+0xad). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int nRadius; } Sphere;

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

extern int func_ov107_020c8eb8(int owner, Sphere *query, int *results);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int ent, int owner, int aux, int mode, Vec3 *dir, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c640(int *node);

void func_ov158_020ce7ec(int *node)
{
    int *state = (int *)node[1];
    int results[4];
    Sphere query;
    Vec3 dir;
    int i;
    int n;

    if (*(int *)(*state + 0x50) == 1) {
        state[0xa] += *(int *)(node[0] + 0x2c);
        if (state[0xa] <= 0xe00) {
            query.pos = *(Vec3 *)(state + 4);
            query.nRadius = FX_Mul(state[0xa], 0x2333);
            n = func_ov107_020c8eb8(*state, &query, results);
            for (i = 0; i < n; i++) {
                VEC_Subtract((Vec3 *)(results[i] + 0x74), &query.pos, &dir);
                func_01ff8d18(&dir, &dir);
                func_01ffa724(0x800, &dir, &dir);
                if (((*(u8 *)((char *)state + 0x30) >> *(u8 *)(results[i] + 0x1b4)) & 1) == 0
                    && func_ov107_020ca918(results[i], *state, *state, 0, &dir, 0) != 0) {
                    func_ov107_020c5af8(*state, 0, 0x53, state + 4);
                    *(u8 *)((char *)state + 0x30) |= 1 << *(u8 *)(results[i] + 0x1b4);
                }
            }
        }
    }
    if (*(u8 *)(state[3] + 0xad) != 0) {
        return;
    }
    func_0203c640(node);
}
