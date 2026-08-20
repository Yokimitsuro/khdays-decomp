typedef unsigned short u16;

/* The queue record this element hands to the collector. */
typedef struct {
    unsigned char bTag;             /* +0x00 */
    unsigned char bPad0[3];
    int nParam;                     /* +0x04 */
    unsigned char bSlot;            /* +0x08 */
    unsigned char bFlag;            /* +0x09 */
    unsigned char bPad1[2];
} Ov002TimeoutRecord;

extern int func_ov002_0207687c(void);
extern short func_02030788(void);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern int func_ov002_020766e0(char *pElement, Ov002TimeoutRecord *pRecord,
                               int nKind);
extern void func_ov002_0207c67c(u16 *pTable, int nTime);
extern void func_ov002_0207903c(char *pElement);

/* Drive a timed element for one frame.
 *
 * While the element is counting down and its game state bit is set, and only
 * for the local player on an enabled owner, the countdown is reduced by the
 * module scale; when it runs out a timeout record is queued and the element is
 * marked reported. In the finishing phase the elapsed counter is advanced
 * instead, the entry table is driven from it, and the element is retired once
 * it reaches the owner's track limit.
 *
 * Two orderings are load-bearing: the record's fields are written tag, slot,
 * flag, then parameter - not in offset order - and the finish test compares
 * the elapsed counter against the limit, not the other way round. */
void *func_ov002_02079488(char *pElement)
{
    char *pOwner;
    int nDelta;
    int nTime;
    int nLimit;
    Ov002TimeoutRecord rec;

    pOwner = *(char **)(pElement + 8);
    nDelta = func_ov002_0207687c();

    if (func_02030788() == 0
        && *(u16 *)(pOwner + 0x7c) != 0
        && *(unsigned char *)(pElement + 0x1b9) == 0
        && ((((unsigned int)(func_020235d0(*(u16 *)(pElement + 0x14),
                                    *(unsigned char *)(pElement + 0x16))
                             & 0xfffe) << 15) >> 16) & 1) == 1) {

        nTime = *(int *)(pElement + 0x1b0) - nDelta;
        *(int *)(pElement + 0x1b0) = nTime;

        if (nTime < 0) {
            rec.bTag = 1;
            rec.bSlot = 0xff;
            rec.bFlag = 0;
            rec.nParam = 0;

            if (func_ov002_020766e0(pElement, &rec, 12) != 0) {
                *(unsigned char *)(pElement + 0x1b9) = 1;
            }

            *(int *)(pElement + 0x1b0) = -1;
        }
    } else if (*(unsigned char *)(pElement + 0x1b9) == 2) {
        nLimit = *(int *)(pOwner + *(unsigned char *)(pElement + 0x1b8) * 4 + 0x84);

        if ((*(u16 *)(pElement + 0x12) & 4) != 0) {
            func_ov002_0207c67c((u16 *)(pElement + 0x3c),
                                *(int *)(pElement + 0x1b4));
        }

        nLimit -= 0x1000;
        nTime = *(int *)(pElement + 0x1b4) + nDelta;
        *(int *)(pElement + 0x1b4) = nTime;

        if (nTime >= nLimit) {
            if ((*(u16 *)(pElement + 0x12) & 4) != 0) {
                func_ov002_0207c67c((u16 *)(pElement + 0x3c), nLimit);
            }
            func_ov002_0207903c(pElement);
        }
    }

    return 0;
}
