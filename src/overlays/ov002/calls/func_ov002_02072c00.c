typedef unsigned char u8;

typedef struct Ov107Object Ov107Object;

typedef struct {
    Ov107Object *pObject;       /* 0x00 */
    u8 gap0004[0x14];
} Ov002ObjectSlot;

typedef struct {
    u8 gap0000[0x44];
    Ov002ObjectSlot *pSlots;    /* 0x44 */
    u8 nSlotsInUse;             /* 0x48 */
    u8 gap0049[9];
    u8 nSeqOut;                 /* 0x52 */
    u8 gap0053[2];
    u8 aPendingSlots[8];        /* 0x55 */
} Ov002ObjectContext;

/* The four bytes the event builds on its own frame: only the slot index at +1
 * is filled in, and the whole thing goes out as command 0xd. */
typedef struct {
    u8 pad0000;
    u8 nSlotIndex;              /* 0x01 */
    u8 pad0002[2];
} Ov002ObjectEventCmd;

extern Ov002ObjectContext *data_ov002_0207fa14;

extern int func_02030788(void);     /* Session_GetLocalPlayerIndex */
extern int func_02030670(void);     /* Session_IsActive */
extern unsigned int func_ov002_0206fb84(int nKind, unsigned short *pBuf);
extern void func_ov002_02072e1c(int nSlotIndex);

/* Reports that one of the screen's objects fired its event.
 *
 * Only the local seat does anything; a guest returns at once.  The object is
 * looked up in the slot array to turn it into an index, which goes out as
 * command 0xd or, with no session running, straight into the local handler.
 *
 * When the session refuses the command the index is parked in the first free
 * byte of the pending list.  Nothing checks that the list had a free byte: with
 * all eight taken, the store goes through a null pointer.
 *
 * The index itself is left as the register found it when the object is not in
 * the array at all -- the ROM only writes it on a match.
 */
void func_ov002_02072c00(Ov107Object *pObject)
{
    Ov002ObjectContext *pCtx;
    Ov002ObjectEventCmd cmd;
    u8 *pPending;
    u8 nIndex;
    int i;
    Ov002ObjectSlot *pSlot;
    int nCount;

    pCtx = data_ov002_0207fa14;
    if (func_02030788() != 0) {
        return;
    }

    i = 0;
    nCount = pCtx->nSlotsInUse;
    if (nCount > 0) {
        pSlot = pCtx->pSlots;
        do {
            if (pSlot->pObject == pObject) {
                nIndex = (u8)i;
                break;
            }
            i++;
            pSlot++;
        } while (i < nCount);
    }
    cmd.nSlotIndex = nIndex;

    if (func_02030670() != 0) {
        if (func_ov002_0206fb84(0xd, (unsigned short *)&cmd) == 0xffff) {
            pPending = 0;
            i = 0;
            do {
                if (pCtx->aPendingSlots[i] == 0xff) {
                    pPending = &pCtx->aPendingSlots[i];
                    break;
                }
                i++;
            } while (i < 8);
            *pPending = nIndex;
        }
        pCtx->nSeqOut++;
    } else {
        func_ov002_02072e1c(cmd.nSlotIndex);
    }
}
