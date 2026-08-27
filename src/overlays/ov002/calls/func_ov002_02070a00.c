typedef signed char s8;
typedef signed short s16;

typedef struct Ov002TaskNode {
    void *pHook0;
    void *pHook1;
    void *pHook2;           /* this function's own slot */
    char pad00c[5];
    s8 nLap;                /* lap timer slot, -1 when the node holds none */
    char pad012[2];
    s16 nKind;
    s16 nResolved;
} Ov002TaskNode;

int func_ov002_02070a00(Ov002TaskNode *pNode, int nPhase);

extern int func_ov002_0207285c(int nKind);      /* kind -> table byte */
extern int func_ov002_0206f6e4(int bStart, int nLap);
extern void func_ov002_02070890(void);
extern void func_ov002_0207087c(void);

/* Writes a hook slot only when the caller hands over something other than -1,
   which is how a caller says "leave this one alone". */
static inline void Ov002_SetHooks(Ov002TaskNode *pNode, void *pA, void *pB,
                                  void *pC)
{
    if (pA != (void *)-1) {
        pNode->pHook0 = pA;
    }
    if (pB != (void *)-1) {
        pNode->pHook1 = pB;
    }
    if (pC != (void *)-1) {
        pNode->pHook2 = pC;
    }
}

/* One node's phase hook.  Phase 0 re-resolves the node's kind; phase 1 stops
   whatever lap it holds and then reinstalls the whole hook triple, this
   function included.  Any other phase does nothing. */
int func_ov002_02070a00(Ov002TaskNode *pNode, int nPhase)
{
    switch (nPhase) {
    case 0:
        if (pNode->nKind >= 0) {
            pNode->nResolved = (s16)func_ov002_0207285c(pNode->nKind);
        }
        break;

    case 1:
        if (pNode->nLap != -1) {
            if (func_ov002_0206f6e4(0, pNode->nLap) < 0) {
                return -1;
            }
        }
        Ov002_SetHooks(pNode, (void *)func_ov002_02070890,
                       (void *)func_ov002_0207087c,
                       (void *)func_ov002_02070a00);
        break;
    }
    return 0;
}
