typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* The 0x14 placement record ov002_PlaceElementNode fills in. */
typedef struct {
    int nKind;                      /* +0x00 */
    int nParamB;                    /* +0x04 */
    int nParamA;                    /* +0x08 */
    int nParamC;                    /* +0x0c */
    int nAngle;                     /* +0x10 */
} Ov002PlaceParams;                 /* 0x14 */

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

/* Build a spawned element's start position: the requested position, raised by
 * half of whichever extent the placement kind selects. Kinds above 3 leave the
 * position alone. */
void func_ov002_0207c53c(VecFx32 *pOut, const VecFx32 *pPos,
                         const Ov002PlaceParams *pParams)
{
    pOut->x = pPos->x;
    pOut->y = pPos->y;
    pOut->z = pPos->z;

    switch (pParams->nKind) {
    case 0:
    case 3:
        pOut->y = pPos->y + FX_Mul(pParams->nParamB, 0x800);
        break;
    case 1:
        pOut->y = pPos->y + FX_Mul(pParams->nParamA + pParams->nParamB, 0x800);
        break;
    case 2:
        pOut->y = pPos->y + FX_Mul(pParams->nParamA, 0x800);
        break;
    }
}
