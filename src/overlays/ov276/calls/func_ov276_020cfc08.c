/* Joint callback of the ov276 enemy: when the render object reports the +0x3b4 joint, its
 * translation becomes that of the +0x3c0 transform and the two +0x3ec transforms are placed
 * 0x433 and 0x866 ahead of it along the actor's +0xa0 orientation; when it reports the +0x3b8
 * joint, its translation becomes that of the +0x444 transform. */
struct Vecx32 { int x, y, z; };
struct MtxFx43 { int m[9]; struct Vecx32 t; };

extern int func_02016320(void *renderObj, struct MtxFx43 *out, void *b, int joint);
extern void func_0203ca30(void *transform, struct Vecx32 *pos);
extern void func_0202f384(struct Vecx32 *dst, void *quat, struct Vecx32 *src);
extern void VEC_Add(struct Vecx32 *a, struct Vecx32 *b, struct Vecx32 *d);

void func_ov276_020cfc08(int item, int actor)
{
    struct MtxFx43 mtx;
    struct Vecx32 v;
    int i;

    if (func_02016320((void *)(*(int *)(item + 0x88) + 0x20), &mtx, 0, *(int *)(actor + 0x3b4)) != 0) {
        func_0203ca30((void *)(actor + 0x3c0), &mtx.t);
        for (i = 0; i < 2; i++) {
            v.x = 0;
            v.y = 0;
            v.z = i == 0 ? 0x866 / 2 : 0x866;
            func_0202f384(&v, (void *)(actor + 0xa0), &v);
            VEC_Add(&v, &mtx.t, &v);
            func_0203ca30((void *)(actor + 0x3ec + i * 0x2c), &v);
        }
    }
    if (func_02016320((void *)(*(int *)(item + 0x88) + 0x20), &mtx, 0, *(int *)(actor + 0x3b8)) != 0) {
        func_0203ca30((void *)(actor + 0x444), &mtx.t);
    }
}
