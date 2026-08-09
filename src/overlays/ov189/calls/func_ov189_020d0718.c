typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct QuerySphere {
    VecFx32 position;
    int radius;
} QuerySphere;

struct Actor {
    u16 flags00;
    u16 id02;
    char pad004[0x70];
    VecFx32 position74;
};

struct Ov189HitReactionState {
    struct Actor *owner;
    char pad004[0x08];
    int reactionContext0c;
    char pad010[0x2d];
    u8 hitMask3d;
};

extern const VecFx32 data_02042258;
extern const VecFx32 data_02041dc8;
extern int func_ov107_020c8eb8(struct Actor *owner, QuerySphere *query,
                               struct Actor **results);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_01ff8d18(VecFx32 *in, VecFx32 *out);
extern void func_01ffa724(int scale, VecFx32 *in, VecFx32 *out);
extern int func_ov107_020ca918(struct Actor *candidate, struct Actor *owner,
                              struct Actor *source, int mode,
                              VecFx32 *direction, int zero);
extern void VEC_Add(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void func_ov107_020c0b90(struct Actor *owner, int mode,
                                VecFx32 position, int zero);
extern void func_ov107_020c5af8(struct Actor *owner, int reactionId,
                                int reactionMode, int context);

void *func_ov189_020d0718(struct Ov189HitReactionState *state, u32 mode,
                          QuerySphere *query, VecFx32 *position, int scale)
{
    int attackMode;
    int count;
    struct Actor *candidates[4];
    QuerySphere localQuery;
    VecFx32 direction;
    VecFx32 output;
    VecFx32 forward;
    VecFx32 zero;
    int i;
    u8 bit;
    void *result = 0;

    if (position != 0) {
        localQuery.position = *position;
        localQuery.radius = 0x400;
        count = func_ov107_020c8eb8(state->owner, &localQuery, candidates);
    } else {
        if (query == 0) {
            return state;
        }
        count = func_ov107_020c8eb8(state->owner, query, candidates);
    }

    i = 0;
    if (count > 0) {
        forward = data_02042258;
        zero = data_02041dc8;
        attackMode = mode & 0xff;
        do {
            bit = (u8)(1 << candidates[i]->id02);
            if ((state->hitMask3d & bit) == 0) {
                VEC_Subtract(&candidates[i]->position74,
                             &state->owner->position74, &direction);
                direction.y = 0;
                if (func_01ff8d18(&direction, &direction) == 0) {
                    direction = forward;
                }
                func_01ffa724(scale, &direction, &direction);
                if (func_ov107_020ca918(candidates[i], state->owner,
                                        state->owner, attackMode,
                                        &direction, 0) != 0) {
                    output = zero;
                    if (position != 0) {
                        output = *position;
                    } else if (query != 0) {
                        VEC_Subtract(&candidates[i]->position74,
                                     &query->position, &output);
                        func_01ff8d18(&output, &output);
                        func_01ffa724(query->radius, &output, &output);
                        VEC_Add(&output, &direction, &output);
                        VEC_Add(&output, &query->position, &output);
                    }
                    func_ov107_020c0b90(state->owner, 0, output, 0);
                    state->hitMask3d |= bit;
                    result = (void *)1;
                }
            }
            i++;
        } while (i < count);
    }

    if (result != 0) {
        switch (mode) {
        case 0:
            func_ov107_020c5af8(state->owner, 0, 0x4e,
                                state->reactionContext0c);
            break;
        case 1:
        case 2:
            func_ov107_020c5af8(state->owner, 0x12f, 5,
                                state->reactionContext0c);
            break;
        }
    }
    return result;
}

