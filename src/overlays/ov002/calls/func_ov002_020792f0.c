typedef unsigned short u16;

/* The 12 byte event this path posts to the element's owner. */
typedef struct {
    unsigned char bKind;            /* +0x00 */
    unsigned char pad01[3];
    int nValue;                     /* +0x04 */
    unsigned char bSource;          /* +0x08 */
    unsigned char bFirstTrack;      /* +0x09 */
    unsigned char pad0a[2];
} Ov002ElementEvent;                /* 0x0c */

extern int func_020235d0(u16 nId, unsigned char nSlot);
extern int func_ov002_0207c788(int nLimit, int nA, int nB);
extern int func_ov002_020766e0(char *pElement, Ov002ElementEvent *pEvent,
                               int nSize);

/* Report a hit on a timed element.
 *
 * Answers 1 when the element is not taking hits at all, 8 when it is but this
 * one does not land, and 0 when the event was posted. An element that has
 * already reported is not asked twice.
 *
 * The three ways of not taking hits are one condition with a single return, so
 * the tail sits between the guard and the body the way the original has it;
 * the "did not land" answers are one nest with a single trailing return.
 */
int func_ov002_020792f0(char *pElement, char *pHit)
{
    char *pOwner;
    Ov002ElementEvent ev;
    int nIndex;
    int bFirstTrack;

    pOwner = *(char **)(pElement + 8);

    if ((*(u16 *)(pElement + 0x12) & 8) == 0 ||
        (*(unsigned char *)(pElement + 0x1bb) & 0x40) != 0 ||
        (*(unsigned char *)(pElement + 0x16) == 2
             ? 0
             : (int)(((unsigned int)(func_020235d0(*(u16 *)(pElement + 0x14),
                                                   *(unsigned char *)(pElement + 0x16))
                                     & 0xfffe) << 15) >> 16) & 4) != 0) {
        return 1;
    }

    if (*(unsigned char *)(pElement + 0x1b9) == 0) {
        nIndex = *(unsigned char *)(pElement + 0x1b8);

        if (func_ov002_0207c788(*(int *)(pOwner + nIndex * 4 + 0x74),
                                *(int *)(pHit + 0x14),
                                *(int *)(pHit + 0x18)) != 0) {
            if (nIndex == 0) {
                bFirstTrack = 1;
            } else {
                bFirstTrack = 0;
            }

            ev.bKind = 1;
            ev.bSource = *(unsigned char *)(pHit + 0xc);
            ev.bFirstTrack = (unsigned char)bFirstTrack;
            ev.nValue = *(int *)(pHit + 0x14);

            if (func_ov002_020766e0(pElement, &ev, 0xc) != 0) {
                *(unsigned char *)(pElement + 0x1b9) = 1;
                return 0;
            }
        }
    }

    return 8;
}
