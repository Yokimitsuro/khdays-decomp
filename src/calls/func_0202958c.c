/* func_0202958c -- update a room box's XZ bounds, MAIN. A box turned by 0 or 180 degrees (+0x44
 * & 0x7fff clear) spans its half extents (+0x38 / +0x40) around its position (+0x2c); otherwise
 * the four corners are rotated (MTX_Rot22) and their extremes, offset by the position, become
 * the bounds (+0xc/+0x10 min, +0x14/+0x18 max). The original initialises the minimum twice (the
 * second pair of stores was meant for the maximum), so the maximum keeps its previous value as
 * the starting point. */
typedef int fx32;
typedef long long s64;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;
typedef struct { fx32 x, z; } XZ;

typedef struct RoomBox {
    char pad00[0xc];
    XZ min;                             /* +0x0c */
    XZ max;                             /* +0x14 */
    char pad1c[0x2c - 0x1c];
    VecFx32 pos;                        /* +0x2c */
    fx32 width;                         /* +0x38 */
    fx32 height;                        /* +0x3c */
    fx32 depth;                         /* +0x40 */
    int angle;                          /* +0x44 */
} RoomBox;

extern const short data_0203d210[];     /* FX_SinCosTable_ */
extern void MTX_Rot22_(MtxFx22 *m, fx32 sinVal, fx32 cosVal);

void func_0202958c(RoomBox *box)
{
    fx32 hw = box->width / 2;
    fx32 hd = box->depth / 2;

    if ((box->angle & 0x7fff) == 0) {
        box->min.x = box->pos.x - hw;
        box->min.z = box->pos.z - hd;
        box->max.x = box->pos.x + hw;
        box->max.z = box->pos.z + hd;
        return;
    }
    {
        XZ corner[4];
        MtxFx22 rot;
        int idx = box->angle >> 4;
        int i;

        MTX_Rot22_(&rot, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
        corner[0].x = (fx32)(((s64)-hw * rot._00 + (s64)-hd * rot._10) >> 12);
        corner[0].z = (fx32)(((s64)-hw * rot._01 + (s64)-hd * rot._11) >> 12);
        corner[1].x = (fx32)(((s64)hw * rot._00 + (s64)-hd * rot._10) >> 12);
        corner[1].z = (fx32)(((s64)hw * rot._01 + (s64)-hd * rot._11) >> 12);
        corner[2].x = (fx32)(((s64)-hw * rot._00 + (s64)hd * rot._10) >> 12);
        corner[2].z = (fx32)(((s64)-hw * rot._01 + (s64)hd * rot._11) >> 12);
        corner[3].x = (fx32)(((s64)hw * rot._00 + (s64)hd * rot._10) >> 12);
        corner[3].z = (fx32)(((s64)hw * rot._01 + (s64)hd * rot._11) >> 12);
        box->min.x = 0x7fffffff;
        box->min.z = 0x7fffffff;
        box->min.x = (fx32)0x80000000;
        box->min.z = (fx32)0x80000000;
        for (i = 0; i < 4; i++) {
            if (box->min.x > corner[i].x) {
                box->min.x = corner[i].x;
            }
            if (box->min.z > corner[i].z) {
                box->min.z = corner[i].z;
            }
            if (box->max.x < corner[i].x) {
                box->max.x = corner[i].x;
            }
            if (box->max.z < corner[i].z) {
                box->max.z = corner[i].z;
            }
        }
        box->min.x += box->pos.x;
        box->min.z += box->pos.z;
        box->max.x += box->pos.x;
        box->max.z += box->pos.z;
    }
}
