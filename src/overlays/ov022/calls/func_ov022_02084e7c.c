typedef unsigned short u16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct Ov022Actor {
    char pad_0000[0x66];
    u16 group66;
} Ov022Actor;

typedef struct CollisionHit {
    char pad_0000[0x0c];
    int distance0c;
} CollisionHit;

extern int func_01fffe14(void);
extern Ov022Actor *func_01fffde0(int index);
extern VecFx32 *func_ov022_020881f8(int index);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern CollisionHit *func_0202c33c(int group, const VecFx32 *origin,
                                    const VecFx32 *direction, int mask);
extern void func_01ffd0e8(int distance, const VecFx32 *direction,
                          const VecFx32 *origin, VecFx32 *out);
extern int VEC_Mag(const VecFx32 *vector);

int func_ov022_02084e7c(int index, const VecFx32 *position)
{
    VecFx32 raisedOrigin;
    VecFx32 direction;
    VecFx32 hitPosition;
    VecFx32 hitDelta;
    Ov022Actor *actor;
    VecFx32 *origin;
    CollisionHit *hit;
    int result = 1;

    actor = func_01fffde0(func_01fffe14());
    origin = func_ov022_020881f8(func_01fffe14());
    VEC_Subtract(position, origin, &direction);
    raisedOrigin = *origin;
    raisedOrigin.y += 0x1000;
    hit = func_0202c33c(actor->group66, &raisedOrigin, &direction, 0xcd);
    if (hit != 0) {
        func_01ffd0e8(hit->distance0c, &direction, &raisedOrigin,
                      &hitPosition);
        VEC_Subtract(&hitPosition, origin, &hitDelta);
        if (VEC_Mag(&direction) > VEC_Mag(&hitDelta)) {
            result = 0;
        }
    }
    return result;
}

