/* func_ov008_02089dc4 -- Ov008_ComputeRecordPrice: price of sorted record nIndex
 * (table +0x38) after its level scaling.  The growth factor is the player's u16
 * level value (GameState 0x1168 + 2 * pRec->nLevelField) over the record's byte
 * divisor (+0x26), both in fx32, truncated to 19 fractional bits and offset by
 * 1.0; that factor is raised to (pRec->nExponent >> 12) - 1 in 64-bit fx math
 * and applied to the base price (+0x8).  The product is brought back to fx32 as
 * `(prod << 12) >> 24` (the ROM's byte-split tail; a plain `>> 12` is shorter).
 */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef long long      s64;
typedef unsigned long long u64;

#define FX32_ONE   0x1000
#define FX32_SHIFT 12
#define FACTOR_MASK 0x7ffff000

typedef struct Ov008ParamRecord {
    u8  pad_00[4];
    int nLevelField;          /* 0x04 */
    u32 nPrice;               /* 0x08 */
    u8  pad_0c[0x14 - 0xc];
    int nExponent;            /* 0x14: fx32 */
    u8  pad_18[0x26 - 0x18];
    u8  nDivisor;             /* 0x26 */
} Ov008ParamRecord;

typedef struct Ov008ParamTable {
    u8 pad_00[0x38];
    Ov008ParamRecord **apSorted;      /* 0x38 */
} Ov008ParamTable;

typedef struct GameState {
    u8  pad_0000[0x1168];
    u16 aLevel[1];            /* 0x1168 */
} GameState;

extern Ov008ParamTable *data_ov008_02090fb0;
extern GameState *data_0204be18;
extern int FX_Inv(int nNumer, int nDenom);                        /* fx32 divide */

u32 func_ov008_02089dc4(int nIndex)
{
    Ov008ParamRecord *pRec;
    s64 nAcc;
    int nPow;
    s64 nFactor;

    pRec = data_ov008_02090fb0->apSorted[nIndex];
    nFactor = (FX_Inv(data_0204be18->aLevel[pRec->nLevelField] << FX32_SHIFT, pRec->nDivisor << FX32_SHIFT) & FACTOR_MASK) + FX32_ONE;
    pRec = data_ov008_02090fb0->apSorted[nIndex];
    nAcc = nFactor;
    for (nPow = (pRec->nExponent >> FX32_SHIFT) - 1; nPow > 0; nPow--) {
        nAcc = (nAcc * nFactor) >> FX32_SHIFT;
    }
    return (u32)(((nAcc * (u64)pRec->nPrice) << 12) >> 24);
}
