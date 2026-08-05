typedef unsigned char u8;

struct Ov234Vec3 {
    int x;
    int y;
    int z;
};

struct Ov234VecBlock {
    struct Ov234Vec3 vector;
    int unused;
};

static inline void Ov234Vec3_Set(struct Ov234Vec3 *vec, int x, int y, int z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline int Ov234FxMul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

struct Ov234ObjectFlags {
    unsigned char bit0 : 1;
    unsigned char bit1 : 1;
    unsigned char rest : 6;
};

struct Ov234Object {
    char pad000[0x2c];
    int frameDelta2c;
    char pad030[0x70];
    struct Ov234Vec3 anchorA0;
    char pad0ac[0x44];
    struct Ov234Vec3 movementF0;
    char pad0fc[0x18];
    struct Ov234Vec3 vector114;
    char pad120[0x5a];
    struct Ov234ObjectFlags flags17a;
    char pad17b[0x23d];
    int value3b8;
};

struct Ov234State {
    struct Ov234Object *object00;
    int field04;
    int node08;
    int field0c;
    struct Ov234Vec3 direction10;
    struct Ov234Vec3 effectPosition1c;
    char pad28[0x0c];
    int angle34;
    int targetAngle38;
    int computedAngle3c;
    int field40;
    int effectTimer44;
    int countdown48;
    char pad4c[0x08];
    int lowerLimit54;
    int verticalStep58;
    int verticalScale5c;
    int field60;
    int preserveDirection64;
    int snapAngle68;
    int reactionLatched6c;
};

struct Ov234Node {
    struct Ov234Object *object;
    struct Ov234State *state;
};

extern const struct Ov234Vec3 data_02042264;
extern const struct Ov234Vec3 data_02041dc8;
extern const short data_0203d210[];

extern int func_0203d040(int, int, int, int);
extern void func_0202f188(struct Ov234Vec3 *,
                         const struct Ov234Vec3 *, int);
extern void func_0203c9d0(struct Ov234Vec3 *, struct Ov234Vec3 *);
extern int VEC_DotProduct(struct Ov234Vec3 *, struct Ov234Vec3 *);
extern void func_01ffa724(int, struct Ov234Vec3 *, struct Ov234Vec3 *);
extern void VEC_Subtract(struct Ov234Vec3 *, struct Ov234Vec3 *,
                         struct Ov234Vec3 *);
extern int func_01ff8d18(struct Ov234Vec3 *, struct Ov234Vec3 *);
extern int func_020050b4(int, int);
extern void func_ov107_020c5af8(struct Ov234Object *, int, int, int);
extern void func_ov107_020c5c54(struct Ov234Object *, struct Ov234Vec3 *);

void func_ov234_020cca84(struct Ov234Node *node)
{
    struct Ov234State *state = node->state;
    struct Ov234VecBlock rotated;
    struct Ov234Vec3 objectVector;
    struct Ov234Vec3 facing;
    struct Ov234Vec3 projected;
    struct Ov234Vec3 oldDirection;
    struct Ov234Vec3 newDirection;
    int turnStep;
    int angleIndex;

    turnStep = node->object->frameDelta2c * 90 / 10;
    if (state->snapAngle68 != 0) {
        state->angle34 = state->targetAngle38;
    } else {
        state->angle34 = func_0203d040(
            state->angle34, state->targetAngle38,
            turnStep, 0);
    }

    func_0202f188(&rotated.vector, &data_02042264, state->angle34);
    func_0203c9d0(&state->object00->anchorA0, &rotated.vector);

    if (state->object00->flags17a.bit1 == 0) {
        state->reactionLatched6c = 0;
    }

    if (state->object00->flags17a.bit1 != 0 &&
        state->object00->flags17a.bit0 == 0 &&
        state->reactionLatched6c == 0) {
        objectVector = state->object00->vector114;
        angleIndex =
            ((int)(unsigned short)((unsigned int)(
                ((long long)state->angle34 * 0x28be60db9391LL +
                 0x80000000000LL) >> 32) >> 12) >> 4);
        Ov234Vec3_Set(&facing,
                      -data_0203d210[angleIndex * 2],
                      0,
                      -data_0203d210[angleIndex * 2 + 1]);
        func_01ffa724(VEC_DotProduct(&facing, &objectVector) << 1,
                      &objectVector, &projected);
        VEC_Subtract(&projected, &facing, &projected);
        func_01ff8d18(&projected, &projected);
        state->computedAngle3c = func_020050b4(projected.x, projected.z);

        oldDirection = state->direction10;
        func_01ffa724(func_01ff8d18(&state->direction10,
                                    &state->direction10),
                      &projected, &newDirection);
        state->direction10.x = newDirection.x;
        state->direction10.y = oldDirection.y;
        state->direction10.z = newDirection.z;
        state->angle34 = state->targetAngle38 =
            func_020050b4(state->direction10.x, state->direction10.z);
        func_ov107_020c5af8(state->object00, 0x178, 4, state->node08);
        state->reactionLatched6c = 1;
    }

    state->object00->movementF0 = state->direction10;

    if (state->object00->flags17a.bit0 != 0) {
        if (state->preserveDirection64 == 0) {
            state->direction10 = data_02041dc8;
        }
    }

    state->direction10.x = Ov234FxMul(state->direction10.x, 0xd00);
    state->direction10.z = Ov234FxMul(state->direction10.z, 0xd00);

    if (*(int *)((char *)state->node08 + 4) > 0x19000) {
        state->direction10.z = Ov234FxMul(state->direction10.z, 0xc00);
    }

    if (state->direction10.y > 0x100) {
        state->direction10.y =
            Ov234FxMul(state->direction10.y, state->verticalScale5c);
    } else if (state->direction10.y > state->lowerLimit54) {
        state->direction10.y += state->verticalStep58;
    }

    state->effectTimer44 += node->object->frameDelta2c;
    if (state->effectTimer44 > 0x77880) {
        func_ov107_020c5c54(state->object00, &state->effectPosition1c);
        state->effectTimer44 = 0;
    }

    if (state->countdown48 > 0) {
        state->countdown48 -= node->object->frameDelta2c;
    } else {
        state->countdown48 = 0;
    }

    if (state->object00->value3b8 < 0x1e) {
        state->lowerLimit54 = -0x280;
        state->verticalStep58 = -0x38;
        state->verticalScale5c = 0xe00;
        state->field60 = 0x400;
        return;
    }
    if (state->object00->value3b8 < 0x32) {
        state->lowerLimit54 = -0x2c0;
        state->verticalStep58 = -0x3c;
        state->verticalScale5c = 0xdc0;
        state->field60 = 0x480;
        return;
    }
    if (state->object00->value3b8 < 0x64) {
        state->lowerLimit54 = -0x300;
        state->verticalStep58 = -0x40;
        state->verticalScale5c = 0xd90;
        state->field60 = 0x500;
        return;
    }
    if (state->object00->value3b8 < 0x96) {
        state->lowerLimit54 = -0x340;
        state->verticalStep58 = -0x44;
        state->verticalScale5c = 0xd60;
        state->field60 = 0x600;
        return;
    }
    state->lowerLimit54 = -0x380;
    state->verticalStep58 = -0x48;
    state->verticalScale5c = 0xd30;
    state->field60 = 0x700;
}
