typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct Ov002RootContext {
    char pad0000[0x8ba8];
    s16 nState;                     /* +0x8ba8 */
} Ov002RootContext;

/* The info block an entry points at; only its code is read here. */
typedef struct Ov002EntryInfo {
    char pad000[0x4c];
    u16 wCode;                      /* +0x4c */
} Ov002EntryInfo;

typedef struct Ov002ListEntry {
    char pad000[8];
    Ov002EntryInfo *pInfo;          /* +0x08 */
    char pad00c[4];
    u8 bCtxIndex;                   /* +0x10 */
    char pad011[3];
    u16 wQueryId;                   /* +0x14 */
    u8 bQuerySlot;                  /* +0x16 */
} Ov002ListEntry;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_01fffe14(void);                 /* the local peer */
extern int func_ov022_02088474(int nPeer);
extern Ov002ListEntry *func_ov002_02076850(int nIndex);   /* one of 0x40 */
extern int func_ov002_0207285c(int nCtxIndex);
extern int func_020235d0(u16 nId, u8 nSlot);

/* Whether the wanted entry of the local peer's kind is one this screen may act
 * on right now.
 *
 * Only three states band at all.  The list is walked from the front counting
 * entries whose context maps to the local peer's kind, and the one asked for
 * is the nWanted'th of them.  It then has to carry the right info code: in the
 * last of the three states that means exactly 0x15, and in the other two one
 * of the pair at 0x1d.
 *
 * nMode 1 asks only whether the entry qualifies at all.  nMode 0 asks the
 * harder question and, in the 0x15 case, also refuses when the entry's query
 * comes back with its low bit set.  Anything else is a no.
 */
int func_ov002_0206c900(int nMode, int nWanted)
{
    Ov002RootContext *pRoot;
    s16 *pState;
    Ov002ListEntry *pEntry;
    int nKind;
    int nState;
    int nInfo;
    int i;
    int nFound;
    int bBusy;

    pRoot = data_ov002_0207fa00;
    pState = &pRoot->nState;
    nKind = func_ov022_02088474(func_01fffe14()) & 0xff;

    if ((u16)(s16)(pRoot->nState - 0x385) <= 2) {
        nFound = -1;
        for (i = 0; i < 0x40; i++) {
            pEntry = func_ov002_02076850(i);
            if (nKind == func_ov002_0207285c(pEntry->bCtxIndex)) {
                nFound++;
                if (nFound == nWanted) {
                    break;
                }
            }
        }

        if (pEntry != 0) {
            nState = *pState;
            if ((nState == 0x387
                 && (nInfo = pEntry->pInfo->wCode) == 0x15)
                || (nState != 0x387
                    && (nInfo = pEntry->pInfo->wCode,
                        (u16)(nInfo + 0xffe3) <= 1))) {
                if (nMode == 1) {
                    return 1;
                }
                if (nMode == 0) {
                    if (nState == 0x387 && nInfo == 0x15) {
                        bBusy = (func_020235d0(pEntry->wQueryId,
                                               pEntry->bQuerySlot) & 1) != 0;
                        if (bBusy == 0) {
                            return 1;
                        }
                    } else {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
