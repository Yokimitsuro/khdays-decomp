typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002Vec3 {
    int x;
    int y;
    int z;
} Ov002Vec3;

/* The stage's linear congruential generator, seeded here from the level. */
typedef struct Ov002Rng {
    int nSeed;
    int nMult;
    int nInc;
} Ov002Rng;

typedef struct Ov002Spawned {
    char pad000[0x30];
    u8 bFlags;
} Ov002Spawned;

typedef struct Ov002SpotStage {
    char pad000[0x4e];
    u16 nRowStride;
    char pad050[4];
    char *pRows;
    char pad058[4];
    void *pFreeBits;        /* one bit per spot id, set while the id is free */
    char pad060[0x24c8];
    Ov002Vec3 aSpots[1];    /* where each spot was last spawned */
} Ov002SpotStage;

typedef struct Ov002SpotHolder {
    char pad000[4];
    Ov002SpotStage *pStage;
} Ov002SpotHolder;

extern Ov002SpotHolder data_ov002_0207fa28;

extern int func_02025694(void *pBits, unsigned int nIndex);  /* bit test */
extern void func_ov002_02077df0(char *pRow);   /* release the row's owner */
extern Ov002Spawned *func_ov002_020775e4(int nIndex, int a1, int a2, int a3,
                                         const Ov002Vec3 *pPlace, int a5,
                                         Ov002Rng *pRng);

/* Spawns the object for one spot and remembers where it went.  If the spot's
   bit is clear it first releases whatever owns its row, so the spot is always
   free before the spawn.  The spawn is handed a three-word seed built on the
   stack: the caller's level shifted up by 14 as the seed, then the fixed
   multiplier and increment. */
void *func_ov002_02077b64(int nIndex, int a1, int a2, int a3,
                          const Ov002Vec3 *pPlace, int a5, u8 bLevel)
{
    Ov002SpotStage *pStage;
    Ov002Spawned *pSpawned;
    Ov002Rng rng;

    pStage = data_ov002_0207fa28.pStage;
    if (func_02025694(pStage->pFreeBits, nIndex) == 0) {
        pStage = data_ov002_0207fa28.pStage;
        func_ov002_02077df0(pStage->pRows + pStage->nRowStride * nIndex);
    }

    rng.nSeed = bLevel << 14;
    rng.nMult = 0x5d588b65;
    rng.nInc = 0x269ec3;
    pSpawned = func_ov002_020775e4(nIndex, a1, a2, a3, pPlace, a5, &rng);
    pSpawned->bFlags = (u8)(pSpawned->bFlags | 4);
    data_ov002_0207fa28.pStage->aSpots[nIndex] = *pPlace;
    return pSpawned;
}
