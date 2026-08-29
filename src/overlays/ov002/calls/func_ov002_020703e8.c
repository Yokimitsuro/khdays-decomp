typedef signed char s8;
typedef signed short s16;

typedef struct VecFx32 {
    int x, y, z;
} VecFx32;

typedef struct Ov002TaskNode Ov002TaskNode;

typedef int (*Ov002NodeHook)(Ov002TaskNode *pNode);
/* Test a node runs against one player's position. */
typedef int (*Ov002NodePlayerTest)(Ov002TaskNode *pNode, VecFx32 *pPos);

/* Only the leading flag word of a player record matters here: bit 16 takes the
   player out of the walk. */
typedef struct Ov002PlayerRecord {
    unsigned long long nFlags;
} Ov002PlayerRecord;

struct Ov002TaskNode {
    Ov002NodeHook pHook0;
    Ov002NodeHook pHook1;
    Ov002NodeHook pHook2;
    int nThreshold;
    s8 nResult;
    s8 nLap;
    char pad012[2];
    Ov002NodePlayerTest pfnTest;
    s8 nMode;               /* 0 reports the first player to pass, 1 needs all */
    char pad019[3];
    s16 nWorld;             /* world the players have to be in */
};

/* Number of players the session currently holds; this caller reads the count
   as a signed int, which is what makes its loop bounds signed. */
extern int func_ov022_020882f8(void);
extern Ov002PlayerRecord *func_01fffde0(int nPlayer);
extern VecFx32 *func_ov022_020881f8(int nPlayer);
extern int func_ov022_02088474(int nPlayer);
/* Starts (bStart != 0) or stops a lap; returns the lap, negative on failure. */
extern int func_ov002_0206f6e4(int bStart, int nLap);
extern int func_ov002_0206f04c(Ov002TaskNode *pNode);
extern int func_ov002_0207060c(Ov002TaskNode *pNode);
extern int func_ov002_0206f0c8(Ov002TaskNode *pNode);

/* Writes a hook slot unless the caller passes -1, which means "leave this one
   as it is". */
static inline void Ov002_SetHook(Ov002NodeHook *pSlot, Ov002NodeHook pHook)
{
    if ((int)pHook != -1) {
        *pSlot = pHook;
    }
}

/* Walks the players the session holds and runs the node's own test against
   each one that is still in play and in the wanted world.  Mode 0 reports the
   first player to pass; mode 1 succeeds only once every player has, and gives
   up as soon as one is in the wrong world or fails the test.  A node that
   comes out with an answer takes a lap of its own when it has a payload
   threshold and waits on the lap finisher, or moves straight to its follow-up
   hook. */
int func_ov002_020703e8(Ov002TaskNode *pNode)
{
    int i;
    VecFx32 *pPos;
    int nWorld;

    pNode->nResult = -2;
    if (pNode->nWorld < 0) {
        return -2;
    }

    switch (pNode->nMode) {
    case 0:
        for (i = 0; i < func_ov022_020882f8(); i++) {
            if ((func_01fffde0(i)->nFlags & 0x10000) == 0) {
                pPos = func_ov022_020881f8(i);
                nWorld = func_ov022_02088474(i);
                if (nWorld == pNode->nWorld) {
                    if (pNode->pfnTest(pNode, pPos) != 0) {
                        pNode->nResult = (s8)i;
                        break;
                    }
                }
            }
        }
        break;

    case 1:
        pNode->nResult = -1;
        for (i = 0; i < func_ov022_020882f8(); i++) {
            if ((func_01fffde0(i)->nFlags & 0x10000) == 0) {
                pPos = func_ov022_020881f8(i);
                nWorld = func_ov022_02088474(i);
                if (nWorld != pNode->nWorld) {
                    pNode->nResult = -2;
                    break;
                }
                if (pNode->pfnTest(pNode, pPos) == 0) {
                    pNode->nResult = -2;
                    break;
                }
            }
        }
        break;
    }

    if (pNode->nResult != -2) {
        if (pNode->nThreshold > 0) {
            pNode->nLap = (s8)func_ov002_0206f6e4(1, -1);
            if (pNode->nLap < 0) {
                return -2;
            }
            Ov002_SetHook(&pNode->pHook0, func_ov002_0206f04c);
            Ov002_SetHook(&pNode->pHook1, 0);
            Ov002_SetHook(&pNode->pHook2, func_ov002_0207060c);
            return -2;
        }
        Ov002_SetHook(&pNode->pHook0, func_ov002_0206f0c8);
        Ov002_SetHook(&pNode->pHook1, 0);
        Ov002_SetHook(&pNode->pHook2, 0);
    }

    return pNode->nResult;
}
