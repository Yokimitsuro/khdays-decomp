/* Bounce entry of the ov204 enemy's ball (and its byte-identical twin): plays animation 9, aims
 * the travel direction from the launch position at the target's +0x190 point (or copies the
 * default direction), flattens and normalises it (falling back to the shared forward vector),
 * sets the speed to 0x1000, clears the phase and the clock, fires reaction 0x132 mode 8 at the
 * reaction point and hands off to the bounce tick. The flattening store is written at the end
 * of both branches: the tail-merged block keeps it ahead of the normalise argument. */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;

typedef struct {
    int actor;
    int pad04;
    Vec3 vel;
    Vec3 defaultDir;
    Vec3 *from;
    Vec3 *at;
    u8 *busy;
    int clock;
    int pad30[4];
    int target;
    u8 pad44;
    u8 phase;
    u8 pad46[2];
    Vec3 dir;
    int speed;
} BallState;

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *d);
extern int func_01ff8d18(const Vec3 *a, Vec3 *d);
extern void func_ov107_020c5af8(int actor, int reaction, int mode, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern void func_ov205_020d5b54(int *node);

void func_ov205_020d5a94(int *node)
{
    BallState *state = (BallState *)node[1];

    func_ov107_020c9264(state->actor, 9, 0);
    if (state->target != 0) {
        VEC_Subtract(state->from, (Vec3 *)(state->target + 0x190), &state->dir);
        state->dir.y = 0;
    } else {
        state->dir = state->defaultDir;
        state->dir.y = 0;
    }
    if (func_01ff8d18(&state->dir, &state->dir) == 0) {
        state->dir = data_02042258;
    }
    state->speed = 0x1000;
    state->phase = 0;
    state->clock = 0;
    func_ov107_020c5af8(state->actor, 0x132, 8, state->at);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov205_020d5b54);
}
