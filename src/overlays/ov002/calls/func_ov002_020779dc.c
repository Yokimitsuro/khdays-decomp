typedef unsigned char u8;
typedef signed char s8;

/* The stage's own linear congruential generator. */
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
    char pad000[0x2518];
    Ov002Rng rng;
} Ov002SpotStage;

typedef struct Ov002SpotHolder {
    char pad000[4];
    Ov002SpotStage *pStage;
} Ov002SpotHolder;

typedef struct Ov002SpotDesc {
    s8 nKind;               /* negative means the kind is not available */
    char pad001[7];
} Ov002SpotDesc;

extern Ov002SpotHolder data_ov002_0207fa28;
extern Ov002SpotDesc data_ov002_0207e67c[];
extern u8 data_0204c240;                /* boot-mode flags */
extern u8 data_0204c248[];

extern int func_ov002_02077560(int nWhich);     /* pick a free spot */
extern Ov002Spawned *func_ov002_020775e4(int nSpot, int nKind, int a1, int a2,
                                         int a3, int a4, Ov002Rng *pRng);

static inline void Ov002_StepRng(Ov002Rng *pRng)
{
    pRng->nSeed = pRng->nMult * pRng->nSeed + pRng->nInc;
}

/* Spawns one object of the requested kind into whichever spot is free.  When
   no spot is free it still burns three draws off the stage's generator, so the
   sequence stays in step whether or not the spawn happened.  Bit 2 is cleared
   on whatever it spawns, the opposite of what Ov002_SpawnSpot does. */
void *func_ov002_020779dc(int nKind, int a1, int a2, int a3, int a4)
{
    Ov002Spawned *pSpawned;
    int nSpot;

    if (data_ov002_0207e67c[nKind].nKind < 0) {
        return 0;
    }

    if ((data_0204c240 & 4) != 0) {
        if (nKind == 2 && data_0204c248[5] == 0) {
            return 0;
        }
    } else {
        if (nKind == 0) {
            return 0;
        }
    }

    nSpot = func_ov002_02077560(0);
    if (nSpot < 0) {
        Ov002_StepRng(&data_ov002_0207fa28.pStage->rng);
        Ov002_StepRng(&data_ov002_0207fa28.pStage->rng);
        Ov002_StepRng(&data_ov002_0207fa28.pStage->rng);
        return 0;
    }

    pSpawned = func_ov002_020775e4(nSpot, nKind, a1, a2, a3, a4,
                                   &data_ov002_0207fa28.pStage->rng);
    pSpawned->bFlags = (u8)(pSpawned->bFlags & ~4);
    return pSpawned;
}
