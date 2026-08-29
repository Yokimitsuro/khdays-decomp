typedef signed char s8;
typedef signed short s16;

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
    s8 nCheck;              /* which of the five checks this node runs */
    s8 nFilter;             /* owner slot the check is narrowed to */
    s16 nEntry;             /* entry the single-entry check reads */
};

extern int func_ov002_020740b0(int nIndex, int nFilter);
extern int func_ov002_02074170(int nFilter, int nScale);
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

/* Runs the check this node was set up with and turns its answer into the
   node's result: the first two ask the entry set directly, the last three ask
   whether the pieces still fit at a given scale.  A node that comes out with
   an answer takes a lap of its own when it has a payload threshold and waits
   on the lap finisher, or moves straight to its follow-up hook. */
int func_ov002_0206ffa4(Ov002TaskNode *pNode)
{
    pNode->nResult = -2;
    if (pNode->nFilter == -2) {
        return 0;
    }

    switch (pNode->nCheck) {
    case 0:
        pNode->nResult = (s8)func_ov002_020740b0(pNode->nEntry,
                                                 pNode->nFilter);
        break;
    case 1:
        pNode->nResult = (s8)func_ov002_020740b0(-1, pNode->nFilter);
        break;
    case 2:
        if (func_ov002_02074170(pNode->nFilter, 0) != 0) {
            pNode->nResult = -1;
        }
        break;
    case 3:
        if (func_ov002_02074170(pNode->nFilter, 0x29) != 0) {
            pNode->nResult = -1;
        }
        break;
    case 4:
        if (func_ov002_02074170(pNode->nFilter, 0xb33) != 0) {
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
