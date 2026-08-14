/* Turn one fade slot on or off.
 *
 * The value the slot reports is the gauge percentage: slot 0 reads it straight
 * out of the context, the others scale their current amount against their
 * maximum through the 64-bit divide helper. A zero result is nudged to 1 so a
 * non-empty gauge never reads as empty.
 *
 * Turning a slot on stamps the tick and arms it for half a second; turning it
 * off hands the value to the redraw with the slot's own callback. Slot 0 also
 * owns the looping sound: it starts on the way up and stops on the way down,
 * unless the shutdown hook has already taken over.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    unsigned long long qwStart;         /* +0x00 */
    int nDuration;                      /* +0x08 */
    int nPhase;                         /* +0x0c */
    int bActive;                        /* +0x10 */
    int nField0014;                     /* +0x14 */
} Ov002FadeSlot;

extern char *data_ov002_0207f618;
extern int data_ov002_0207de04;

extern void func_ov002_0205779c(void);
extern void func_ov002_02057848(void);
extern long long func_02020400(int nNumerator, int nDenominator);
extern unsigned long long func_020031d4(void);
extern void func_ov002_02058340(int nIndex, Ov002FadeSlot *pSlot);
extern void func_ov002_020582d0(int nHandle, int nIndex, unsigned int nValue,
                                void *pfnDraw, int bEmpty);
extern int func_ov002_0206b7a4(void);
extern void func_02033b24(int nBank, int nSound);
extern void func_02033bb4(int nBank, int nSound, int nFlag);

void func_ov002_020593b4(int nIndex, unsigned int bOn) {
    char *ctx = data_ov002_0207f618;
    Ov002FadeSlot *slot = (Ov002FadeSlot *)(ctx + 0x6c + nIndex * 0x18);
    unsigned int nValue;
    void *pfnDraw;
    int nPlaying;

    if (nIndex == 0) {
        nValue = *(u16 *)(ctx + 0x112);
        pfnDraw = (void *)func_ov002_0205779c;
        if (nValue == 0 && *(u16 *)(ctx + 0xce) != 0) {
            nValue = 1;
        }
    } else {
        unsigned int nAmount = *(u16 *)(ctx + nIndex * 4 + 0xce);

        pfnDraw = (void *)func_ov002_02057848;
        nValue = (unsigned int)func_02020400(
                     nAmount * *(int *)((char *)&data_ov002_0207de04
                                        + nIndex * 0xc),
                     *(u16 *)(ctx + nIndex * 4 + 0xcc)) & 0xffff;
        if (nValue == 0 && nAmount != 0) {
            nValue = 1;
        }
    }

    if (slot->bActive != bOn) {
        if (bOn != 0) {
            slot->bActive = 1;
            slot->nField0014 = 0;
            slot->nDuration = 261828;
            slot->nPhase = 0;
            slot->qwStart = func_020031d4();
            func_ov002_02058340(nIndex, slot);
        } else {
            int bEmpty = 0;

            slot->bActive = 0;
            if (*(u16 *)(ctx + nIndex * 4 + 0xce) == 0) {
                bEmpty = 1;
            }
            func_ov002_020582d0(((int *)ctx)[nIndex], nIndex, nValue,
                                pfnDraw, bEmpty);
        }
    }

    if (nIndex != 0) {
        return;
    }

    nPlaying = *(int *)(ctx + 0x30);

    if (bOn != 0) {
        if (nPlaying != 0) {
            return;
        }
        if (func_ov002_0206b7a4() != 0) {
            return;
        }
        func_02033b24(0, 8);
        *(int *)(ctx + 0x30) = 1;
    } else {
        if (nPlaying == 0) {
            return;
        }
        func_02033bb4(0, 8, 0);
        *(int *)(ctx + 0x30) = 0;
    }
}
