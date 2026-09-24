/* func_02039958 -- axis-aligned bounds of an oriented box, MAIN. The box has a centre (+0x00), three
 * unit axes (+0x0c/+0x18/+0x24) and three half extents (+0x30/+0x34/+0x38); each axis is scaled by its
 * half extent (func_01ffa724), the eight corners are built from the centre with every sign
 * combination, and the per-component minimum and maximum over the corners are written out. */
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;

typedef struct OrientedBox {
    VecFx32 centre;                     /* +0x00 */
    VecFx32 axis[3];                    /* +0x0c */
    fx32 half[3];                       /* +0x30 */
} OrientedBox;

typedef struct BoundsFx32 {
    fx32 min[3];                        /* +0x00 */
    fx32 max[3];                        /* +0x0c */
} BoundsFx32;

extern void func_01ffa724(fx32 scale, const VecFx32 *v, VecFx32 *out);  /* scale a vector */
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void func_02039958(BoundsFx32 *out, const OrientedBox *box)
{
    VecFx32 e[3];
    VecFx32 corner[8];
    int i;
    int j;

    func_01ffa724(box->half[0], &box->axis[0], &e[0]);
    func_01ffa724(box->half[1], &box->axis[1], &e[1]);
    func_01ffa724(box->half[2], &box->axis[2], &e[2]);

    VEC_Subtract(&box->centre, &e[0], &corner[0]);
    VEC_Subtract(&corner[0], &e[1], &corner[0]);
    VEC_Subtract(&corner[0], &e[2], &corner[0]);

    VEC_Add(&box->centre, &e[0], &corner[1]);
    VEC_Subtract(&corner[1], &e[1], &corner[1]);
    VEC_Subtract(&corner[1], &e[2], &corner[1]);

    VEC_Add(&box->centre, &e[0], &corner[2]);
    VEC_Add(&corner[2], &e[1], &corner[2]);
    VEC_Subtract(&corner[2], &e[2], &corner[2]);

    VEC_Subtract(&box->centre, &e[0], &corner[3]);
    VEC_Add(&corner[3], &e[1], &corner[3]);
    VEC_Subtract(&corner[3], &e[2], &corner[3]);

    VEC_Subtract(&box->centre, &e[0], &corner[4]);
    VEC_Subtract(&corner[4], &e[1], &corner[4]);
    VEC_Add(&corner[4], &e[2], &corner[4]);

    VEC_Add(&box->centre, &e[0], &corner[5]);
    VEC_Subtract(&corner[5], &e[1], &corner[5]);
    VEC_Add(&corner[5], &e[2], &corner[5]);

    VEC_Add(&box->centre, &e[0], &corner[6]);
    VEC_Add(&corner[6], &e[1], &corner[6]);
    VEC_Add(&corner[6], &e[2], &corner[6]);

    VEC_Subtract(&box->centre, &e[0], &corner[7]);
    VEC_Add(&corner[7], &e[1], &corner[7]);
    VEC_Add(&corner[7], &e[2], &corner[7]);

    out->min[0] = corner[0].x;
    out->min[1] = corner[0].y;
    out->min[2] = corner[0].z;
    out->max[0] = corner[0].x;
    out->max[1] = corner[0].y;
    out->max[2] = corner[0].z;
    for (i = 1; i < 8; i++) {
        for (j = 0; j < 3; j++) {
            if (((fx32 *)&corner[i])[j] < out->min[j]) {
                out->min[j] = ((fx32 *)&corner[i])[j];
            }
            if (((fx32 *)&corner[i])[j] > out->max[j]) {
                out->max[j] = ((fx32 *)&corner[i])[j];
            }
        }
    }
}
