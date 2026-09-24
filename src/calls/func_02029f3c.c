/* func_02029f3c -- build the wall plane of a rotated box for a contact, MAIN. The box is rotated
 * about Y by its +0x44 angle; side -1 (+0x80 of the contact) is the direction from the box centre
 * to the contact point (+0x10), flattened and normalised; sides 0..3 are the -Z, +Z, -X and +X
 * faces, whose normal is a (negated) row of the rotation and whose point is the half extent
 * (+0x38 / +0x40) along it. The plane gets a flat fx16 normal (+0x14), its distance (+0x1c) through
 * the face point moved to the box position (+0x2c), and the box's +0x24 tag (+0x80). */
typedef short fx16;
typedef int fx32;
typedef long long s64;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx16 x, y, z; } VecFx16;
typedef struct { fx32 _00, _01, _10, _11; } MtxFx22;

typedef struct RoomBox {
    char pad00[0x24];
    int tag;                            /* +0x24 */
    int pad28;
    VecFx32 pos;                        /* +0x2c */
    fx32 width;                         /* +0x38 */
    fx32 height;                        /* +0x3c */
    fx32 depth;                         /* +0x40 */
    int angle;                          /* +0x44 */
} RoomBox;

typedef struct RoomContact {
    char pad00[0x10];
    VecFx32 pos;                        /* +0x10 */
    char pad1c[0x80 - 0x1c];
    int side;                           /* +0x80 */
} RoomContact;

typedef struct RoomPlane {
    char pad00[0x14];
    VecFx16 n;                          /* +0x14 */
    short pad1a;
    fx32 d;                             /* +0x1c */
    char pad20[0x80 - 0x20];
    int tag;                            /* +0x80 */
} RoomPlane;

extern const short data_0203d210[];     /* FX_SinCosTable_ */
extern void MTX_Rot22_(MtxFx22 *m, fx32 sinVal, fx32 cosVal);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void func_01ffcfd0(const VecFx32 *v, VecFx16 *n);   /* normalise into fx16 */
extern fx32 VEC_DotProductFx16(const VecFx32 *a, const VecFx16 *b);

void func_02029f3c(const RoomBox *box, const RoomContact *c, RoomPlane *pl)
{
    MtxFx22 rot;
    VecFx32 v;
    int idx = box->angle >> 4;
    s64 hx;
    s64 hz;

    MTX_Rot22_(&rot, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    hx = box->width / 2;
    hz = box->depth / 2;
    switch (c->side) {
    case -1:
        VEC_Subtract(&c->pos, &box->pos, &v);
        v.y = 0;
        func_01ffcfd0(&v, &pl->n);
        break;
    case 0:
        pl->n.x = -rot._10;
        pl->n.z = -rot._11;
        v.x = (fx32)((-hx * rot._10) >> 12);
        v.z = (fx32)((-hz * rot._11) >> 12);
        break;
    case 1:
        pl->n.x = rot._10;
        pl->n.z = rot._11;
        v.x = (fx32)((hx * rot._10) >> 12);
        v.z = (fx32)((hz * rot._11) >> 12);
        break;
    case 2:
        pl->n.x = -rot._00;
        pl->n.z = -rot._01;
        v.x = (fx32)((-hx * rot._00) >> 12);
        v.z = (fx32)((-hz * rot._01) >> 12);
        break;
    case 3:
        pl->n.x = rot._00;
        pl->n.z = rot._01;
        v.x = (fx32)((hx * rot._00) >> 12);
        v.z = (fx32)((hz * rot._01) >> 12);
        break;
    }
    v.x += box->pos.x;
    v.z += box->pos.z;
    v.y = 0;
    pl->n.y = 0;
    pl->d = VEC_DotProductFx16(&v, &pl->n);
    pl->tag = box->tag;
}
