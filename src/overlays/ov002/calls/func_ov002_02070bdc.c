typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;

typedef struct Ov002TaskNode Ov002TaskNode;

typedef int (*Ov002NodeHook)(Ov002TaskNode *pNode);

struct Ov002TaskNode {
    Ov002NodeHook pHook0;
    Ov002NodeHook pHook1;
    Ov002NodeHook pHook2;
    int nThreshold;
    s8 nResult;
    s8 nLap;
    char pad012[2];
    u8 nStat;               /* which per-player value the node tallies */
    u8 nMode;               /* how the tally is turned into a result */
    char pad016[2];
    int nGoal;              /* value the tally has to reach */
};

/* Number of players the session currently holds; this caller reads the
   count as a signed int, which is what makes its loop bounds signed. */
extern int func_ov022_020882f8(void);
/* One player's value out of the session slot table. */
extern u16 func_ov002_0206bdcc(int nSlot, int nIndex);
/* Starts (bStart != 0) or stops a lap; returns the lap, negative on failure. */
extern int func_ov002_0206f6e4(int bStart, int nLap);
extern int func_ov002_0206f04c(Ov002TaskNode *pNode);
extern int func_ov002_0206f0c8(Ov002TaskNode *pNode);

/* Writes a hook slot unless the caller passes -1, which means "leave this one
   as it is". */
static inline void Ov002_SetHook(Ov002NodeHook *pSlot, Ov002NodeHook pHook)
{
    if ((int)pHook != -1) {
        *pSlot = pHook;
    }
}

/* Tallies one value across the players in the session and decides whether the
   node's goal has been met: mode 0 reports the first player to reach it, mode
   1 reports success only once every player has, and mode 2 adds the value up
   across the whole session.  A node that comes out with an answer takes a lap
   of its own when it has a payload threshold and waits on the lap finisher,
   or moves straight to its follow-up hook. */
int func_ov002_02070bdc(Ov002TaskNode *pNode)
{
    int i;
    int nTotal;

    pNode->nResult = -2;
    switch (pNode->nMode) {
    case 0:
        for (i = 0; i < func_ov022_020882f8(); i++) {
            if (pNode->nGoal <= func_ov002_0206bdcc(i, pNode->nStat)) {
                pNode->nResult = (s8)i;
                break;
            }
        }
        break;

    case 1:
        if (func_ov022_020882f8() > 0) {
            pNode->nResult = -1;
            for (i = 0; i < func_ov022_020882f8(); i++) {
                if (pNode->nGoal > func_ov002_0206bdcc(i, pNode->nStat)) {
                    pNode->nResult = -2;
                    break;
                }
            }
        }
        break;

    case 2:
        nTotal = 0;
        for (i = 0; i < func_ov022_020882f8(); i++) {
            nTotal += func_ov002_0206bdcc(i, pNode->nStat);
        }
        if (pNode->nGoal <= nTotal) {
            pNode->nResult = -1;
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
            Ov002_SetHook(&pNode->pHook2, 0);
            return -2;
        }
        Ov002_SetHook(&pNode->pHook0, func_ov002_0206f0c8);
        Ov002_SetHook(&pNode->pHook1, 0);
        Ov002_SetHook(&pNode->pHook2, 0);
    }

    return pNode->nResult;
}
