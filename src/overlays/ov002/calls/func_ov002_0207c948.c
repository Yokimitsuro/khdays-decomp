typedef struct {
    int x;
    int y;
    int z;
} Vec3;

/* A stored spot: a position plus the index of the party slot it belongs to. */
typedef struct {
    Vec3 vPos;                      /* +0x00 */
    unsigned char bSlot;            /* +0x0c */
} Ov002Spot;

extern int VEC_Mag(const Vec3 *v);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *ab);
extern int func_01ff8d18(const Vec3 *v, Vec3 *pUnit);
extern void func_01ffa724(int nFactor, const Vec3 *pSrc, Vec3 *pDst);
extern Vec3 *func_ov002_02076cc8(int nObj);
extern int func_ov022_020882f8(void);
extern Vec3 *func_ov022_020881f8(int nSlot);

/* Pull a spot in towards its party member when it is closer than a radius.
 *
 * The spot's horizontal distance is measured with its height zeroed. If that
 * is inside the radius and the spot belongs to a live party slot, the spot is
 * replaced by the direction from the object to that member, scaled out to the
 * radius. The original height is put back either way.
 */
void func_ov002_0207c948(int nObj, const Ov002Spot *pSpot, int nRange,
                         Vec3 *pOut)
{
    int nSlot;
    Vec3 *pFrom;

    *pOut = pSpot->vPos;
    pOut->y = 0;

    if (nRange > VEC_Mag(pOut)) {
        nSlot = pSpot->bSlot;
        if (nSlot < func_ov022_020882f8()) {
            pFrom = func_ov002_02076cc8(nObj);
            VEC_Subtract(pFrom, func_ov022_020881f8(nSlot), pOut);
            func_01ff8d18(pOut, pOut);
            func_01ffa724(nRange, pOut, pOut);
        }
    }

    pOut->y = pSpot->vPos.y;
}
