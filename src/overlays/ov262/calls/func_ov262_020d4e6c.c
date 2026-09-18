/* Grab-slot flight of the ov261 enemy (and its byte-identical twin): flies from the +4 position
 * towards the +0x2c point of the +0x48 grab slot. On the first tick a direction within 0xc00 of
 * vertical replaces the +0x74 axis with the up vector and the direction with the forward one
 * (unit length 0x800). After 0x2000 of accumulated frame-time the +0x1c anchor faces the point,
 * the list's first entry is released (slot +0x3ad, not carried), the +0x2c word points at the
 * slot's point and the state ends with sub-state 2. Otherwise the +0x30 velocity is 0x800 along
 * the axis-cross-direction, blended back towards the direction beyond 0x1800 and towards its
 * reverse under 0x800 of distance; the +0x3c rate is the frame-time * 30 / 5 and the anchor
 * faces the velocity. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern void VEC_Subtract(void *a, void *b, void *d);
extern int func_01ff8d18(void *a, void *d);
extern int VEC_DotProduct(const struct Vecx32 *a, const struct Vecx32 *b);
extern void func_ov262_020d3f88(void *anchor, struct Vecx32 *dir, const struct Vecx32 *pos);
extern void func_ov015_02080c00(int piece, int slot, int carried, int a);
extern void func_0203c634(int *node, int slot, void *cb);
extern void VEC_CrossProduct(void *a, void *b, void *d);
extern int FX_Inv(int a, int b);
extern void func_01ffa724(int scale, void *v, void *d);
extern void VEC_Add(void *a, void *b, void *d);
extern const struct Vecx32 data_02042264;
extern const struct Vecx32 data_02042258;
extern const struct Vecx32 data_02041dc8;

void func_ov262_020d4e6c(int *node)
{
    int *state = (int *)node[1];
    struct Vecx32 dir;
    struct Vecx32 side;
    int slot;
    int len;
    int t;

    slot = *(int *)(*state + 0x3a0) + 0x18 + *(u8 *)(state + 0x12) * 0x24;
    VEC_Subtract((void *)(slot + 0x14), (void *)state[1], &dir);
    len = func_01ff8d18(&dir, &dir);
    if (state[0x10] == 0) {
        t = VEC_DotProduct(&dir, &data_02042264);
        if (t < 0) {
            t = -t;
        }
        if (t > 0xc00) {
            *(struct Vecx32 *)(state + 0x1d) = data_02042264;
            dir = data_02042258;
            len = 0x800;
        }
    }
    state[0x10] += *(int *)(*node + 0x2c);
    if (state[0x10] >= 0x2000) {
        func_ov262_020d3f88(state + 7, &dir, &data_02041dc8);
        func_ov015_02080c00(*(int *)(*(int *)(*state + 0x3a0)), *(u8 *)(*state + 0x3ad), 0, 0);
        state[0xb] = slot + 0x14;
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_CrossProduct(state + 0x1d, &dir, &side);
    if (len >= 0x1800) {
        t = FX_Inv(len - 0x1800, 0x800);
        if (t > 0x1000) {
            t = 0x1000;
        } else if (t < 0) {
            t = 0;
        }
        func_01ffa724(0x1000 - t, &side, &side);
        func_01ffa724(t, &dir, &dir);
        VEC_Add(&side, &dir, &side);
    } else if (len < 0x800) {
        t = FX_Inv(0x800 - len, 0x800);
        if (t > 0x1000) {
            t = 0x1000;
        } else if (t < 0) {
            t = 0;
        }
        func_01ffa724(-0x1000, &dir, &dir);
        func_01ffa724(0x1000 - t, &side, &side);
        func_01ffa724(t, &dir, &dir);
        VEC_Add(&side, &dir, &side);
    }
    func_01ffa724(0x800, &side, state + 0xc);
    state[0xf] = *(int *)(*node + 0x2c) * 30 / 5;
    func_ov262_020d3f88(state + 7, &side, &data_02041dc8);
}
