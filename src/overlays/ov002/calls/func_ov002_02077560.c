typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SpotStage {
    char pad000[0x50];
    u16 nSpotCount;             /* how many spot ids exist */
    char pad052[0xa];
    u32 *pFreeBits;             /* one bit per id, set while the id is free */
} Ov002SpotStage;

typedef struct Ov002SpotHolder {
    char pad000[4];
    Ov002SpotStage *pStage;
} Ov002SpotHolder;

extern Ov002SpotHolder data_ov002_0207fa28;

/* mwcc 3.0 has no CLZ intrinsic, so the one instruction has to be spelled out;
   everything around it is ordinary C. */
static inline u32 Clz(u32 nValue)
{
    asm { clz nValue, nValue }
    return nValue;
}

/* Finds the lowest free spot id, or -1 when the band is full.  The bitmap is
   numbered MSB-first, so CLZ of a word gives the lowest free id inside it and
   the walk steps a word at a time with the base rising by 32.

   The two bands are separate id pools sharing one bitmap: bLowBand searches
   from id 0 and refuses anything from 32 up, which is the band handed to an
   owner, while a zero starts at word 1, so id 32, and refuses anything at or
   past nSpotCount, which is the band the spawner draws from.  Only the id is
   found here; clearing the bit is the caller's job. */
int func_ov002_02077560(int bLowBand)
{
    u32 *pBits;
    int nBase;
    int nBit;
    int nId;

    nBase = 0;
    if (bLowBand != 0) {
        pBits = data_ov002_0207fa28.pStage->pFreeBits;
    } else {
        nBase = 0x20;
        pBits = data_ov002_0207fa28.pStage->pFreeBits + 1;
    }

    for (;;) {
        nBit = Clz(*pBits);
        if (nBit < 0x20) {
            nId = nBit + nBase;
            if (bLowBand != 0) {
                if (nId >= 0x20) {
                    return -1;
                }
                return nId;
            }
            if (nId >= data_ov002_0207fa28.pStage->nSpotCount) {
                return -1;
            }
            return nId;
        }
        pBits++;
        nBase += 0x20;
    }
}
