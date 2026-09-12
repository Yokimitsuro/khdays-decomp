typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

typedef struct Box {
    VecFx32 center;
    VecFx32 axis[3];
    fx32 halfExtent[3];
} Box;

extern void VEC_Subtract(int *a, int *b, int *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ffa724(int factor, int *src, int *dst);
extern void VEC_Add(int *a, int *b, int *out);

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((long long)a * b + 0x800) >> 12);
}

/* Squared distance from a point to an oriented box, with the closest point on
 * the box optionally written out through the three pointer outputs. */
fx32 func_02037188(VecFx32 *point, Box *box, fx32 *outX, fx32 *outY, fx32 *outZ) {
    VecFx32 diff;
    fx32 local[3];
    VecFx32 closest;
    fx32 sum;
    int i;

    sum = 0;
    VEC_Subtract((int *)point, (int *)box, (int *)&diff);

    for (i = 0; i < 3; i++) {
        fx32 d = VEC_DotProduct(&diff, &box->axis[i]);
        fx32 halfExtent = box->halfExtent[i];
        local[i] = d;
        if (d < -halfExtent) {
            fx32 pen = d + halfExtent;
            sum += FX_Mul(pen, pen);
            local[i] = -halfExtent;
        } else if (d > halfExtent) {
            fx32 pen = d - halfExtent;
            sum += FX_Mul(pen, pen);
            local[i] = halfExtent;
        }
    }

    closest = box->center;
    for (i = 0; i < 3; i++) {
        VecFx32 scaled;
        func_01ffa724(local[i], (int *)&box->axis[i], (int *)&scaled);
        VEC_Add((int *)&closest, (int *)&scaled, (int *)&closest);
    }

    if (outX) *outX = closest.x;
    if (outY) *outY = closest.y;
    if (outZ) *outZ = closest.z;

    return sum;
}
