/* Grab walk of the ov261 enemy (and its byte-identical twin): the +0x3c rate is the frame-time
 * (30/30); the flat direction to the +0x2c point of the grab slot selected by the +0x6c index
 * (through the +0x49 slot order) sets the +0x1c facing anchor, and the +0x30 velocity is the
 * +0xc orientation's forward vector scaled by an eighth of its (non-negative) alignment with the
 * direction, capped at the remaining distance; the +0x34 lift eases by a fiftieth towards 0x2000
 * above the +0x13c height. Within 0x1000 of the point the slot becomes the +0x48 current one,
 * the index advances and, past the +0x70 count, the tick hands off to the release decision. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern void func_ov261_020d0348(void *anchor, struct Vecx32 *dir, const struct Vecx32 *pos);
extern void func_0202f384(struct Vecx32 *dst, void *quat, const struct Vecx32 *src);
extern int VEC_DotProduct(const struct Vecx32 *a, const struct Vecx32 *b);
extern void func_01ffa724(int scale, void *v, void *d);
extern void func_0203c634(int *node, int slot, void *cb);
extern const struct Vecx32 data_02041dc8;
extern const struct Vecx32 data_02042258;
extern void func_ov261_020d110c(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov261_020d0f90(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 goal;
    struct Vecx32 dir;
    struct Vecx32 fwd;
    int len;
    int speed;
    int d;
    int list;

    len = *(int *)(*node + 0x2c) * 30 / 30;
    list = *(int *)(*state + 0x3a0);
    state[0xf] = len;
    goal = *(struct Vecx32 *)(list + *(u8 *)((char *)state + state[0x1b] + 0x49) * 0x24 + 0x2c);
    VEC_Subtract(&goal, (void *)state[1], &dir);
    dir.y = 0;
    len = func_01ff8d18(&dir, &dir);
    func_ov261_020d0348(state + 7, &dir, &data_02041dc8);
    func_0202f384(&fwd, state + 3, &data_02042258);
    speed = VEC_DotProduct(&fwd, &dir);
    if (speed < 0) {
        speed = 0;
    }
    speed = FX_Mul(speed, 0x200);
    if (len < speed) {
        speed = len;
    }
    func_01ffa724(speed, &fwd, state + 0xc);
    d = 0x2000 - *(int *)(*state + 0x13c);
    state[0xd] += d / 50;
    if (len >= 0x1000) {
        return;
    }
    *(u8 *)(state + 0x12) = *(u8 *)((char *)state + state[0x1b] + 0x49);
    state[0x1b]++;
    if (state[0x1b] >= state[0x1c]) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov261_020d110c);
    }
}
