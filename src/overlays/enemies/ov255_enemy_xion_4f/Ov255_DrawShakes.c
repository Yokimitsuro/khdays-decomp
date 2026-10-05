/* Draw handler of the ov255 shake entries: the camera-facing turn (from data_0204227c towards the
 * scene's +0x7c direction) is set as the global base rotation; every live entry (0x38 bytes) of
 * the +0x90 table is drawn with the +0x88 model's +0x78 mesh at its +0x2c point, scaled by its
 * offset, with polygon id = its handle, alpha = strength x 31 and a colour fading from white to
 * red with the strength. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct { int w[4]; } Quat;
struct Shake { int offset; int strength; char pad08[0x10]; int handle; char pad1c[0x10]; VecFx32 at; };
struct G3Glb { char pad[0xc4]; VecFx32 scale; };

extern int *Ov107_GetActorManager(void);
extern void Quat_FromTwoVectors(Quat *out, const VecFx32 *a, const VecFx32 *b);
extern void Mtx33_FromQuat(void *mtx, const Quat *q);
extern void NNS_G3dGlbSetBaseTrans(const VecFx32 *v);
extern void Gfx_ApplyBaseTransform(void);
extern void NNS_G3dMdlSetMdlPolygonIDAll(int model, int id);
extern void NNS_G3dMdlSetMdlAlpha(int model, int mat, int alpha);
/* Defined taking rgb as GXRgb: declared narrower here, which is what makes mwcc truncate the
 * argument at the call as the ROM does (declared as defined, the code comes out different). */
extern void NNS_G3dMdlSetMdlDiffAll(int model, u16 rgb);
extern void NNS_G3dDraw1Mat1Shp(int model, int a, int b, int c);
extern const VecFx32 data_0204227c;
extern char data_02047428[];
extern struct G3Glb NNS_G3dGlb;

static inline void VEC_Set(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

static inline short ClampColor(short v)
{
    return v > 31 ? 31 : (v < 0 ? 0 : v);
}

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void Ov255_DrawShakes(char *self)
{
    Quat q;
    int i;
    int off;

    Quat_FromTwoVectors(&q, &data_0204227c, (VecFx32 *)(*Ov107_GetActorManager() + 0x7c));
    Mtx33_FromQuat(data_02047428, &q);
    i = 0;
    if (*(int *)(self + 0x8c) > 0) {
        do {
            struct Shake *e = &(*(struct Shake **)(self + 0x90))[i];

            if (e->offset != 0) {
                int alpha;
                int c;
                short g;
                short b;

                alpha = (e->strength * 31) >> 12;
                VEC_Set(&NNS_G3dGlb.scale, e->offset, e->offset, e->offset);
                NNS_G3dGlbSetBaseTrans(&e->at);
                Gfx_ApplyBaseTransform();
                NNS_G3dMdlSetMdlPolygonIDAll(*(int *)(*(int *)(self + 0x88) + 0x78), e->handle);
                NNS_G3dMdlSetMdlAlpha(*(int *)(*(int *)(self + 0x88) + 0x78), 0, alpha);
                c = (FX_Mul(e->strength, 0x1400) * 31) >> 12;
                g = ClampColor(c);
                b = ClampColor(c - 16);
                NNS_G3dMdlSetMdlDiffAll(*(int *)(*(int *)(self + 0x88) + 0x78), (u16)((b << 10) | (31 | (g << 5))));
                NNS_G3dDraw1Mat1Shp(*(int *)(*(int *)(self + 0x88) + 0x78), 0, 0, 1);
            }
        } while (++i < *(int *)(self + 0x8c));
    }
}
