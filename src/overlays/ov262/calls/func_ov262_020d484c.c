/* Hover aim tick of the ov261 enemy (and its byte-identical twin): the speed is thirty frame-times
 * over fifteen, the anchor follows the partner's position (+0x3a8 part, +0x74), and when the
 * orientation's forward vector faces the partner (dot above 0xf00) the clock resets, reaction
 * 0x179 mode 4 fires at the actor's position and the tick hands off to the hover entry.
 * Codegen: the partner position is held as a pointer variable (`pos`); a plain `int part` local
 * leaves the /15 quotient in ip instead of the ROM's r6. */
typedef struct { int x, y, z; } Vec3;
typedef struct { int x, y, z, w; } Quat;

typedef struct {
    int actor;
    Vec3 *pos;
    int pad08;
    Quat orient;
    Vec3 anchor;
    int pad28[2];
    Vec3 jitter;
    int speed;
    int clock;
} HoverState;

extern void func_ov262_020d3f88(Vec3 *anchor, Vec3 *pos, Vec3 *target);
extern void func_0202f384(Vec3 *dst, Quat *orient, const Vec3 *src);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *d);
extern int func_01ff8d18(const Vec3 *a, Vec3 *d);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_ov107_020c5af8(int actor, int reaction, int mode, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov262_020d4918(int *node);

void func_ov262_020d484c(int *node)
{
    HoverState *state = (HoverState *)node[1];
    Vec3 fwd;
    Vec3 dir;
    Vec3 *pos;

    state->speed = *(int *)(*node + 0x2c) * 30 / 15;
    pos = (Vec3 *)(*(int *)(state->actor + 0x3a8) + 0x74);
    func_ov262_020d3f88(&state->anchor, pos, state->pos);
    func_0202f384(&fwd, &state->orient, &data_02042258);
    VEC_Subtract(pos, state->pos, &dir);
    func_01ff8d18(&dir, &dir);
    if (VEC_DotProduct(&fwd, &dir) > 0xf00) {
        state->clock = 0;
        func_ov107_020c5af8(state->actor, 0x179, 4, state->pos);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov262_020d4918);
    }
}
