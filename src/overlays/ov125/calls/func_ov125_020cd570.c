/* Dive tick of the ov125 enemy: reseeds the +0x3c counter with 3 times the owner's rate
 * (30/10) and acquires the target with its squared distance -- none sends it to sub-state 2.
 * The gap (root distance less both radii) rebuilds the look-at at +0x68 and sets the blend
 * t = (4.0 - gap) / 4.0 clamped to +-1.0; the step at +8 is the look-at's forward (turned by
 * data_02042258) scaled by -t plus the sideways component (up x forward, up being the +0x78
 * orbit sense) scaled by 1.0 - |t|, both at 0x280, with a fixed -0x180 fall speed. While the
 * +0x54 count is spent a 0x65 roll re-arms it to a random value between the actor's +0x224 and
 * +0x228 and picks sub-state 6 (under 20 with an idle aim node), 7 (under 80) or 5; otherwise
 * the 020cd27c state takes over once the +0x13c height drops under 0x2000.
 * `+ (v - v)` is the documented copy artifact of func_02023eb4 (`add r4,r0,#0`). */
typedef struct { int x, y, z; } Vec3;

static inline void VEC_Set(Vec3 *v, int x, int y, int z) {
    v->x = x;
    v->y = y;
    v->z = z;
}

extern int func_ov107_020cab14(int obj, int *pSqDist);
extern void func_0203c634(int node, int slot, void *cb);
extern int FX_Sqrt(int a);
extern void func_0203cd7c(void *out, void *a, int b, void *c);
extern void func_0202ea48(void *a, void *b);
extern int FX_Inv(int num, int den);
extern void func_0202f384(void *out, void *pose, void *k);
extern void VEC_CrossProduct(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_02023eb4(int bound);
extern int func_ov125_020ce594(int node);
extern int data_02042264;
extern int data_02042258;
extern void func_ov125_020cd27c(void);

void func_ov125_020cd570(int *node)
{
    int owner;
    int *state = (int *)node[1];
    int buf[9];
    Vec3 up;
    Vec3 sideN;
    Vec3 side;
    Vec3 fwd;
    int sq;
    int actor;
    int target;
    int t;
    int v;
    int lo;
    int diff;

    owner = *state;
    state[0xf] = *(int *)(node[0] + 0x2c) * 30 / 10;
    target = state[1] = func_ov107_020cab14(*state, &sq);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    actor = *state;
    sq = FX_Sqrt(sq) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    func_0203cd7c(buf, (void *)(state[1] + 0x74), state[9], &data_02042264);
    func_0202ea48(state + 0x1a, buf);
    t = FX_Inv(0x4000 - sq, 0x4000);
    if (t < -0x1000) t = -0x1000;
    if (t > 0x1000) t = 0x1000;
    func_0202f384(&fwd, state + 0x1a, &data_02042258);
    VEC_Set(&up, 0, state[0x1e] << 12, 0);
    VEC_CrossProduct(&up, &fwd, &sideN);
    func_01ffa724(0x1000 - (t < 0 ? -t : t), &sideN, &sideN);
    func_01ffa724(-t, &fwd, &side);
    func_01ffa724(0x280, &sideN, &sideN);
    func_01ffa724(0x280, &side, &side);
    VEC_Add(&sideN, &side, (Vec3 *)(state + 2));
    state[3] = -0x180;
    if (state[0x15] <= 0) {
        int r = func_02023eb4(0x65) + (v - v);
        lo = *(int *)(*state + 0x224);
        diff = *(int *)(*state + 0x228) - lo;
        if (diff < 0) {
            diff = -diff;
        }
        state[0x15] = lo + func_02023eb4(diff + 1);
        if (r < 0x14 && func_ov125_020ce594(*(int *)(*state + 0x390)) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 6;
            func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
            return;
        }
        if (r < 0x50) {
            *(unsigned char *)(*state + 0x1c7) = 7;
            func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
            return;
        }
        *(unsigned char *)(*state + 0x1c7) = 5;
        func_0203c634((int)node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    if (*(int *)(owner + 0x13c) >= 0x2000) {
        return;
    }
    func_0203c634((int)node, *(signed char *)((int)node + 0x20), &func_ov125_020cd27c);
}
