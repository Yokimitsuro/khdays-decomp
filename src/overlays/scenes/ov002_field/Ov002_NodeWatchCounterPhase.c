
#include "nitro/types.h"

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
    int nCounter;           /* which running counter the node watches */
    int nGoal;              /* seconds the counter has to reach */
};

/* Running counters, all in raw OS ticks. */
extern u64 Ov002_GetStartTicks(void);
extern u64 Ov002_GetEndTicks(void);
extern u64 Ov002_GetTimeoutTicks(void);
extern u64 Ov002_GetTimeoutRemaining(void);
extern u64 Ov002_GetRemainingTicks(void);
/* 64-bit divide; 0x82ea ticks make up one second at 64x resolution. */
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
extern int Ov002_NodeGetResult(Ov002TaskNode *pNode);

/* Writes a hook slot unless the caller passes -1, which means "leave this one
   as it is". */
static inline void Ov002_SetHook(Ov002NodeHook *pSlot, Ov002NodeHook pHook)
{
    if ((int)pHook != -1) {
        *pSlot = pHook;
    }
}

/* Watches one of the running counters and reports success once it has been
   going for as long as the node asks.  A goal of zero passes straight away and
   a counter that has not started yet leaves the node waiting; otherwise the
   tick count is turned into seconds and measured against the goal.  The last
   counter is a plain on/off one and passes while it reads zero.  A node that
   comes out with an answer moves on to its follow-up hook. */
int Ov002_NodeWatchCounterPhase(Ov002TaskNode *pNode)
{
    int nGoal;
    u64 qTicks;

    pNode->nResult = -2;
    switch (pNode->nCounter) {
    case 0:
        nGoal = pNode->nGoal;
        qTicks = Ov002_GetStartTicks();
        if (nGoal == 0) {
            pNode->nResult = -1;
            break;
        }
        if (qTicks == 0) {
            break;
        }
        if (func_02020368(qTicks << 6, 0x82ea) >= (u64)nGoal) {
            pNode->nResult = -1;
        }
        break;

    case 1:
        nGoal = pNode->nGoal;
        qTicks = Ov002_GetEndTicks();
        if (nGoal == 0) {
            pNode->nResult = -1;
            break;
        }
        if (qTicks == 0) {
            break;
        }
        if (func_02020368(qTicks << 6, 0x82ea) >= (u64)nGoal) {
            pNode->nResult = -1;
        }
        break;

    case 2:
        nGoal = pNode->nGoal;
        qTicks = Ov002_GetTimeoutTicks();
        if (nGoal == 0) {
            pNode->nResult = -1;
            break;
        }
        if (qTicks == 0) {
            break;
        }
        if (func_02020368(qTicks << 6, 0x82ea) >= (u64)nGoal) {
            pNode->nResult = -1;
        }
        break;

    case 3:
        nGoal = pNode->nGoal;
        qTicks = Ov002_GetTimeoutRemaining();
        if (nGoal == 0) {
            pNode->nResult = -1;
            break;
        }
        if (qTicks == 0) {
            break;
        }
        if (func_02020368(qTicks << 6, 0x82ea) >= (u64)nGoal) {
            pNode->nResult = -1;
        }
        break;

    case 4:
        if (Ov002_GetRemainingTicks() == 0) {
            pNode->nResult = -1;
        }
        break;
    }

    if (pNode->nResult != -2) {
        Ov002_SetHook(&pNode->pHook0, Ov002_NodeGetResult);
        Ov002_SetHook(&pNode->pHook1, 0);
        Ov002_SetHook(&pNode->pHook2, 0);
    }

    return pNode->nResult;
}
