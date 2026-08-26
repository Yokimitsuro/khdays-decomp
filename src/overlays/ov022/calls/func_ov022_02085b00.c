typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022ActorNode {
    char pad_0000[0x80];
    u16 angle80;
} Ov022ActorNode;

typedef struct Ov022Actor {
    char pad_0000[9];
    u8 index9;
    char pad_000a[0x16];
    Ov022ActorNode *node20;
    char pad_0024[0x454];
    s16 angle478;
    char pad_047a[0x12];
    VecFx32 position48c;
} Ov022Actor;

extern const s16 data_0203d210[];

extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *vector);
extern void func_01ff8d18(const VecFx32 *source, VecFx32 *destination);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int func_020358f4(int index, int parameter);

void func_ov022_02085b00(Ov022Actor *actor, const VecFx32 *targetPosition,
                          VecFx32 *result, int mode)
{
    VecFx32 direction;
    VecFx32 facing;
    int distance;
    int angle;
    int facingDot;
    int bestDistance;
    int alternateDot;
    const s16 *table;
    const VecFx32 *actorPosition;

    result->x = 0x7fffffff;
    result->y = -1;
    result->z = mode;

    actorPosition = &actor->position48c;
    distance = func_01ff8e94(targetPosition, actorPosition);
    VEC_Subtract(targetPosition, actorPosition, &direction);
    if (VEC_Mag(&direction) != 0) {
        func_01ff8d18(&direction, &direction);
    }

    direction.y = 0;
    angle = (u16)(actor->node20->angle80 - 0x8000);
    angle >>= 4;
    table = data_0203d210;
    facing.x = -table[angle << 1];
    facing.z = -table[(angle << 1) + 1];
    facing.y = 0;
    facingDot = VEC_DotProduct(&facing, &direction);

    bestDistance = 0x9000;
    if (func_020358f4(actor->index9, 0x55) != 0) {
        bestDistance = 0xd800;
    }

    angle = actor->angle478 >> 4;
    table = data_0203d210;
    facing.x = -table[angle << 1];
    facing.z = -table[(angle << 1) + 1];
    facing.y = 0;
    alternateDot = VEC_DotProduct(&facing, &direction);

    if (distance <= 0x3000) {
        result->x = distance;
        if (facingDot >= 0x0ab8) {
            result->y = 3;
            return;
        }
        result->y = 2;
        return;
    }

    if (distance <= 0x5000) {
        result->x = distance;
        if (alternateDot >= 0x0ab8) {
            result->y = 1;
            return;
        }
        result->y = 0;
        return;
    }

    if (distance <= bestDistance) {
        result->x = distance;
        result->y = 0;
        return;
    }

    if (distance <= 0x1e000) {
        result->x = distance;
        result->y = -1;
    }
}

