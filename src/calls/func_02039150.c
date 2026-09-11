typedef int fx32;

typedef struct VecFx32 {
    fx32 x;
    fx32 y;
    fx32 z;
} VecFx32;

/* Same oriented box as func_02037188, which runs the identical per-axis
 * clamp against halfExtent[] and is the nearest solved neighbour. */
typedef struct Box {
    VecFx32 center;
    VecFx32 axis[3];
    fx32 halfExtent[3];
} Box;

/* The real definition (libs/nitro/fx/calls/FX_Inv.c) reads only its first
 * argument, but this call site loads and passes a second one. An undeclared
 * trailing parameter is how mwcc reserves that register, so declaring one
 * argument here drops a load the ROM performs. */
extern int FX_Inv(int x, int y);

static inline fx32 FX_Mul(fx32 a, fx32 b)
{
    return (fx32)(((long long)a * b + 0x800) >> 12);
}

/*
 * Clamp three per-axis distances against a box's half-extents.
 *
 * axis0 is pinned: its remaining slack is optionally reported through outInv
 * as FX_Inv(slack), and the distance is then snapped to the half-extent
 * outright. axis1 and axis2 are clamped to +/- their half-extent, and every
 * clamp that actually fires adds the square of the overshoot to *penaltySum.
 *
 * delta0 must be a separate local rather than an index at the use site or a
 * self-redefinition of deltaArr: it is what places the deltaArr fetch in the
 * entry block after the callee-saved parameter loads, where the ROM has it.
 */
void func_02039150(int axis0, int axis1, int axis2, fx32 *axisDist, fx32 *deltaArr,
                    Box *box, fx32 *outInv, fx32 *penaltySum)
{
    fx32 *delta0 = deltaArr + axis0;
    if (outInv) {
        *outInv = FX_Inv(box->halfExtent[axis0] - axisDist[axis0], *delta0);
    }
    axisDist[axis0] = box->halfExtent[axis0];

    {
        fx32 halfExtent = box->halfExtent[axis1];
        fx32 dist = axisDist[axis1];
        if (dist < -halfExtent) {
            fx32 pen = dist + halfExtent;
            *penaltySum += FX_Mul(pen, pen);
            axisDist[axis1] = -box->halfExtent[axis1];
        } else if (dist > halfExtent) {
            fx32 pen = dist - halfExtent;
            *penaltySum += FX_Mul(pen, pen);
            axisDist[axis1] = box->halfExtent[axis1];
        }
    }

    {
        fx32 halfExtent = box->halfExtent[axis2];
        fx32 dist = axisDist[axis2];
        if (dist < -halfExtent) {
            fx32 pen = dist + halfExtent;
            *penaltySum += FX_Mul(pen, pen);
            axisDist[axis2] = -box->halfExtent[axis2];
        } else if (dist > halfExtent) {
            fx32 pen = dist - halfExtent;
            *penaltySum += FX_Mul(pen, pen);
            axisDist[axis2] = box->halfExtent[axis2];
        }
    }
}
