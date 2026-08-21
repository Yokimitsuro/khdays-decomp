typedef unsigned short u16;

/* The 20 byte placement record this helper builds on the stack, hands to the
 * scene-node placement call and then copies back to the caller's scratch. */
typedef struct {
    int nKind;                      /* +0x00 */
    int nParamB;                    /* +0x04 */
    int nParamA;                    /* +0x08 */
    int nParamC;                    /* +0x0c */
    int nAngle;                     /* +0x10 */
} Ov002PlaceParams;                 /* 0x14 */

extern int func_0202b87c(int nNode, int nZero, void *pObj,
                         Ov002PlaceParams *pParams, int nFlag);
extern void MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);

/* Place a spawned element's scene node.
 *
 * Kind 3 is an alias for kind 0. A kind that does not fit in a byte, or is
 * above 2, is not a placement the node call understands: the record is stamped
 * with -1 and the call is made without it, and the helper reports zero.
 *
 * The fourth argument is passed by every caller but never read here.
 */
int func_ov002_0207c4c0(void *pObj, int nNode, void *pOut, int nUnused,
                        int nKind, int nParamA, int nParamB, int nParamC,
                        int nAngle, int nFlag)
{
    int bPlaced = 0;
    Ov002PlaceParams params;

    if (nKind == 3) {
        nKind = 0;
    }

    if ((unsigned char)nKind <= 2) {
        params.nKind = nKind;
        params.nParamA = nParamA;
        params.nParamB = nParamB;
        params.nParamC = nParamC;
        params.nAngle = nAngle;
        func_0202b87c(nNode, 0, pObj, &params, nFlag);
        bPlaced = 1;
    } else {
        params.nKind = -1;
        params.nParamA = nParamA;
        params.nParamB = nParamB;
        params.nParamC = nParamC;
        params.nAngle = nAngle;
        func_0202b87c(nNode, 0, pObj, 0, nFlag);
    }

    if (pOut != 0) {
        MI_CpuCopy8(&params, pOut, 0x14);
    }

    return bPlaced;
}
