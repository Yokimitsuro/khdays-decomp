#pragma thumb on
/* func_02028a64 -- build the planes of a collision polygon with vertical edge planes, MAIN (THUMB).
 * Like func_02028924: the face plane (+0x14 fx16 normal, +0x1c distance) comes from the first two
 * edges, and a face whose normal has no horizontal part is flagged (+0x10 bit 1). The edge planes
 * (+0x20) are built against the fixed up axis (data_020420d0) instead of the face normal, so they
 * stand vertical; each distance is taken at the edge's first vertex. The first parameter is
 * unused. */
typedef short fx16;
typedef int fx32;

typedef struct { fx32 x, y, z; } VecFx32;
typedef struct { fx16 x, y, z; } VecFx16;

typedef struct RoomPlane {
    VecFx16 n;                          /* +0x00 */
    short pad06;
    fx32 d;                             /* +0x08 */
} RoomPlane;

typedef struct RoomPoly {
    char pad00[0x10];
    unsigned short flags;               /* +0x10 */
    unsigned short count;               /* +0x12 */
    RoomPlane face;                     /* +0x14 */
    RoomPlane edge[4];                  /* +0x20 */
    VecFx32 v[4];                       /* +0x50 */
} RoomPoly;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);
extern fx32 VEC_DotProductFx16(const VecFx32 *a, const VecFx16 *b);
extern void func_01ffcfd0(const VecFx32 *v, VecFx16 *n);                        /* normalise into fx16 */
extern const VecFx16 data_020420d0;     /* the up axis */
extern void func_01ffcf48(const VecFx32 *a, const VecFx16 *b, VecFx32 *axb);   /* cross with an fx16 vector */

void func_02028a64(void *unused, RoomPoly *poly)
{
    VecFx32 e0;
    VecFx32 e1;
    VecFx32 c;
    VecFx32 *v = poly->v;
    RoomPlane *edge = poly->edge;

    VEC_Subtract(&v[1], &v[0], &e0);
    VEC_Subtract(&v[2], &v[0], &e1);
    VEC_CrossProduct(&e0, &e1, &c);
    func_01ffcfd0(&c, &poly->face.n);
    poly->face.d = VEC_DotProductFx16(&v[0], &poly->face.n);
    if ((poly->face.n.x | poly->face.n.z) == 0) {
        poly->flags |= 2;
    }

    VEC_Subtract(&v[0], &v[1], &e0);
    func_01ffcf48(&e0, &data_020420d0, &c);
    func_01ffcfd0(&c, &edge[0].n);
    edge[0].d = VEC_DotProductFx16(&v[0], &edge[0].n);

    VEC_Subtract(&v[1], &v[2], &e0);
    func_01ffcf48(&e0, &data_020420d0, &c);
    func_01ffcfd0(&c, &edge[1].n);
    edge[1].d = VEC_DotProductFx16(&v[1], &edge[1].n);

    if (poly->count == 3) {
        VEC_Subtract(&v[2], &v[0], &e0);
        func_01ffcf48(&e0, &data_020420d0, &c);
        func_01ffcfd0(&c, &edge[2].n);
        edge[2].d = VEC_DotProductFx16(&v[2], &edge[2].n);
    } else {
        VEC_Subtract(&v[2], &v[3], &e0);
        func_01ffcf48(&e0, &data_020420d0, &c);
        func_01ffcfd0(&c, &edge[2].n);
        edge[2].d = VEC_DotProductFx16(&v[2], &edge[2].n);

        VEC_Subtract(&v[3], &v[0], &e0);
        func_01ffcf48(&e0, &data_020420d0, &c);
        func_01ffcfd0(&c, &edge[3].n);
        edge[3].d = VEC_DotProductFx16(&v[3], &edge[3].n);
    }
}
#pragma thumb off
