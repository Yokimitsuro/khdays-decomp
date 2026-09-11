typedef struct { int x, y, z; } VecFx32;

extern int func_01ff8d18(const VecFx32 *source, VecFx32 *dest);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void func_01ffa724(int scale, VecFx32 *src, VecFx32 *dst);

struct State {
    char pad00[4];
    VecFx32 *pos;
    char pad08[4];
    VecFx32 velocity;
    char pad18[0x18];
    int done;
};

struct Task {
    char pad00[0x214];
    struct State *state;
};

int func_ov299_020d41c0(struct Task *task, void *target, void *aim) {
    struct State *state = task->state;
    VecFx32 buf;
    int ok;

    if (state->done != 0) {
        return 0;
    }

    ok = func_01ff8d18((VecFx32 *)((char *)aim + 4), &buf);
    if (ok == 0) {
        if (target != 0) {
            VEC_Subtract(state->pos, (VecFx32 *)((char *)target + 0x190), &buf);
            buf.y = 0;
            ok = func_01ff8d18(&buf, &buf);
        }
        if (ok == 0) {
            int negZ = -state->velocity.z;
            int negX = -state->velocity.x;
            buf.x = negX;
            buf.y = 0;
            buf.z = negZ;
            func_01ff8d18(&buf, &buf);
        }
    }

    func_01ffa724(0x600, &buf, &state->velocity);
    state->velocity.y += 0x500;
    state->done = 1;
    return 1;
}
