/* func_ov016_020801a0 -- Ov016_FollowerPieceHolds: does player piece pPiece keep its follower
 * held?  A piece that is not live (bit 0 of +0x60) or is closer than 0x2800 to the follower
 * (pFrom) holds; one in state 3 or 6 (+0x179), or flagged 2 / 4 at +0x1ac, does not; otherwise
 * it holds only when it is within nRange + 0x1800 of the anchor pAt and the angle between
 * (pFrom - pAt) and (piece - pAt) is inside the half-cone nCone / 2 (cos from the sin/cos table).  nAngle is not used. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct VecFx32 { int x, y, z; } VecFx32;

typedef struct Ov016LiveFlags {
    unsigned short lowByte : 8;
    unsigned short highByte : 8;
} Ov016LiveFlags;

typedef struct Ov016Piece {
    u8 pad_000[0x60];
    u16 nLiveFlags;           /* 0x60 */
    u8 pad_062[0xb0 - 0x62];
    VecFx32 position;         /* 0xb0 */
    u8 pad_0bc[0x179 - 0xbc];
    u8 nState;                /* 0x179 */
    u8 pad_17a[0x1ac - 0x17a];
    u16 nMoveFlags;           /* 0x1ac */
} Ov016Piece;

extern int  func_01ff8e94(const VecFx32 *pA, const VecFx32 *pB);          /* VEC_Distance */
extern void VEC_Subtract(const VecFx32 *pA, const VecFx32 *pB, VecFx32 *pOut);
extern void func_01ff8d18(VecFx32 *pVec, VecFx32 *pOut);                  /* VEC_Normalize */
extern int  VEC_DotProduct(const VecFx32 *pA, const VecFx32 *pB);
extern const short data_0203d210[];                                       /* FX_SinCosTable_ */

int func_ov016_020801a0(Ov016Piece *pPiece, VecFx32 *pFrom, int nRange, VecFx32 *pAt, int nAngle, int nCone)
{
    VecFx32 position;
    VecFx32 toFrom;
    VecFx32 toPiece;

    if ((((Ov016LiveFlags *)&pPiece->nLiveFlags)->lowByte & 1) == 0) {
        return 1;
    }
    if (pPiece->nState == 3) {
        return 0;
    }
    if (pPiece->nState == 6) {
        return 0;
    }
    if (pPiece->nMoveFlags & 4) {
        return 0;
    }
    if (pPiece->nMoveFlags & 2) {
        return 0;
    }
    position = pPiece->position;
    if (func_01ff8e94(&position, pFrom) < 0x2800) {
        return 1;
    }
    if (func_01ff8e94(&position, pAt) > nRange + 0x1800) {
        return 0;
    }
    VEC_Subtract(pFrom, pAt, &toFrom);
    func_01ff8d18(&toFrom, &toFrom);
    VEC_Subtract(&position, pAt, &toPiece);
    func_01ff8d18(&toPiece, &toPiece);
    return VEC_DotProduct(&toFrom, &toPiece) >= data_0203d210[((nCone / 2) >> 4) * 2 + 1];
}
