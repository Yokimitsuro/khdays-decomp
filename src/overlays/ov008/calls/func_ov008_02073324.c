/* func_ov008_02073324 -- Ov008_BlinkMissionListDots: advance the mission
 * list's dot blink.  Nothing until 0x1991b ticks have passed since the last
 * step (+0x60); then the phase (+0x5e) advances modulo 8 and is folded into
 * a 0..4 brightness step (phases 5..7 mirror 3..1).  Every dot set in the
 * blink mask (+0x5c, 12 bits) gets its tag redrawn in block 954c at value
 * 0x11 + i: dots below the first mission count (0205b958(0)) use tag set
 * 0x19 / 0x17 / 0x14 / 0x16 / 0x18 (row 3), dots below the first plus the
 * second count the set 0x1f / 0x1d / 0x1a / 0x1c / 0x1e (row 2) and the
 * rest 0x25 / 0x23 / 0x20 / 0x22 / 0x24 (row 2).  The step tick is stored.
 */
typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef unsigned long long u64;

#define BLINK_TICKS  0x1991b
#define BLINK_PHASES 8
#define DOT_COUNT    12
#define DOT_TAG_BASE 0x11

typedef struct Ov008MissionList {
    u8  pad_00[0x5c];
    u16 nBlinkMask;           /* 0x5c: dots that blink */
    u16 nBlinkPhase;          /* 0x5e */
    u64 nBlinkTick;           /* 0x60 */
} Ov008MissionList;

extern long long func_020031d4(void);                                     /* GetTick64 */
extern int  func_ov008_02050c3c(void);                                    /* Ov008_GetCtxBlock954c */
extern int  func_ov008_0205b958(int nGroup);                              /* mission count of a group */
extern void func_ov008_0206fe50(int nOwner, u32 nTag, short nX, short nY); /* Ov008_SetTagValueDup */

void func_ov008_02073324(Ov008MissionList *pList)
{
    u64 nNow;
    int nOwner;
    int i;
    int nFirst;
    int nSecond;
    int nValue;
    u32 nTag;
    int nStep;

    nNow = func_020031d4();
    if (nNow < pList->nBlinkTick + BLINK_TICKS) {
        return;
    }
    pList->nBlinkPhase++;
    if (pList->nBlinkPhase >= BLINK_PHASES) {
        pList->nBlinkPhase = 0;
    }
    nOwner = func_ov008_02050c3c();
    nStep = pList->nBlinkPhase;
    if (nStep > 4) {
        nStep = BLINK_PHASES - nStep;
    }
    nFirst = func_ov008_0205b958(0);
    nSecond = func_ov008_0205b958(1);
    nValue = DOT_TAG_BASE;
    for (i = 0; i < DOT_COUNT; nValue++, i++) {
        if ((pList->nBlinkMask & (1 << i)) != 0) {
            if (i < nFirst) {
                nTag = 0x19;
                switch (nStep) {
                case 0:
                    nTag = 0x19;
                    break;
                case 1:
                    nTag = 0x17;
                    break;
                case 2:
                    nTag = 0x14;
                    break;
                case 3:
                    nTag = 0x16;
                    break;
                case 4:
                    nTag = 0x18;
                    break;
                }
                func_ov008_0206fe50(nOwner, nTag, (short)nValue, 3);
            } else if (i < nFirst + nSecond) {
                nTag = 0x1f;
                switch (nStep) {
                case 0:
                    nTag = 0x1f;
                    break;
                case 1:
                    nTag = 0x1d;
                    break;
                case 2:
                    nTag = 0x1a;
                    break;
                case 3:
                    nTag = 0x1c;
                    break;
                case 4:
                    nTag = 0x1e;
                    break;
                }
                func_ov008_0206fe50(nOwner, nTag, (short)nValue, 2);
            } else {
                nTag = 0x25;
                switch (nStep) {
                case 0:
                    nTag = 0x25;
                    break;
                case 1:
                    nTag = 0x23;
                    break;
                case 2:
                    nTag = 0x20;
                    break;
                case 3:
                    nTag = 0x22;
                    break;
                case 4:
                    nTag = 0x24;
                    break;
                }
                func_ov008_0206fe50(nOwner, nTag, (short)nValue, 2);
            }
        }
    }
    pList->nBlinkTick = nNow;
}
