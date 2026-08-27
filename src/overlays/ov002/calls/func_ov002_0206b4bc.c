typedef struct Ov002Vec3 {
    int x;
    int y;
    int z;
} Ov002Vec3;

/* One entry of the session screen's marker table. */
typedef struct Ov002SessionMarker {
    Ov002Vec3 place;
    int nOwner;
    int nKind;              /* left alone when the caller passes -1 */
    char szName[0x30];
} Ov002SessionMarker;

typedef struct Ov002SessionBlock {
    char pad00[4];
    Ov002SessionMarker *pMarkers;
} Ov002SessionBlock;

extern char *data_ov002_0207fa00;

extern int func_01fffe14(void);                 /* the active slot */
extern int func_ov002_0207285c(int nKind);      /* kind -> table byte */
extern void func_ov002_02072874(const char *pName, int nSlot,
                                Ov002Vec3 *pPlace, int *pOwner, int nIndex);
extern int func_02023588(int nFlagId);          /* progress flag set */
extern void func_ov002_02069878(Ov002Vec3 *pPlace, int nOwner, int nIndex,
                                Ov002Vec3 *pOut);
extern void func_0201f924(char *pDst, const char *pSrc);

/* Fills in one marker of the session screen's table and always returns 1.  An
   nIndex of -1 means take the slot func_01fffe14 hands back, but only the table
   write uses that substitute: the placement solver still gets the caller's
   original index.  With a name, the kind is resolved to a slot and, if it
   resolves, the placement is handed to func_ov002_02072874 and the name is
   dropped so it is not copied again below.  Without a name, the placement goes
   through func_ov002_02069878 unless the caller skips it or flag 0x20e7 is
   already set. */
int func_ov002_0206b4bc(int nIndex, int nKind, const Ov002Vec3 *pPlace,
                        int nOwner, const char *pName, int bSkipSolver)
{
    Ov002SessionBlock *pBlock;
    Ov002Vec3 out;
    Ov002Vec3 place;
    int nOwnerLocal;
    int nIdx;
    const char *pPending;
    int nSlot;

    pBlock = (Ov002SessionBlock *)(data_ov002_0207fa00 + 0x8bcc);
    pPending = pName;
    place = *pPlace;
    nIdx = nIndex;
    nOwnerLocal = nOwner;

    if (nIdx == -1) {
        nIdx = func_01fffe14();
    }

    if (pName != 0) {
        nSlot = func_ov002_0207285c(nKind);
        if (nSlot >= 0) {
            func_ov002_02072874(pName, nSlot, &place, &nOwnerLocal, nIdx);
            pPending = 0;
        }
        out = place;
    } else if (bSkipSolver == 0 && func_02023588(0x20e7) == 0) {
        func_ov002_02069878(&place, nOwnerLocal, nIndex, &out);
    } else {
        out = place;
    }

    pBlock->pMarkers[nIdx].place = out;
    pBlock->pMarkers[nIdx].nOwner = nOwnerLocal;
    if (nKind != -1) {
        pBlock->pMarkers[nIdx].nKind = nKind;
    }

    if (pPending != 0) {
        func_0201f924(pBlock->pMarkers[nIdx].szName, pPending);
    } else {
        pBlock->pMarkers[nIdx].szName[0] = 0;
    }
    return 1;
}
