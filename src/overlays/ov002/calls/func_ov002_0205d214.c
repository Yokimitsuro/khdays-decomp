/* Dispatch one input on the panel screen.
 *
 * The raw input is normalised and both the old mode and the new code are run
 * through the classifier, which also hands back a column in an out parameter.
 * The new code's class selects the case: a mode change rebuilds the panel, a
 * column move clamps to the last column when the index runs past the count or
 * lands on a 0xff entry, a list move clamps against whichever list is
 * populated, the cancel case disarms the tag tracker and suppresses the sound
 * by forcing the id negative, and the restore case copies back the default
 * kind. The sound is then played, and the mode stored and the panel reapplied.
 *
 * Two arguments, not four: the third and fourth registers are written before
 * any read, and the pushed r3 slot is only ever the classifier's out parameter.
 * The normaliser likewise takes one argument.
 */
typedef unsigned char u8;

typedef struct {
    u8 bKind;           /* +0 */
    u8 bMode;           /* +1 */
    u8 bIndex;          /* +2 */
    u8 bPanelRow;       /* +3 */
    u8 bKey;            /* +4 */
    u8 pad0005[2];
    u8 bSpare7;         /* +7 */
    u8 pad0008[0x28];
    u8 bColumns;        /* +0x30 */
    u8 bRowSpan;        /* +0x31 */
    u8 aBitIndex[2];    /* +0x32, stride 2 */
} Ov002PanelSession;

extern Ov002PanelSession *data_ov002_0207f620;

extern void func_ov002_0205cbd0(void);
extern int func_ov002_0205bbbc(int nRaw);
extern int func_ov002_0205a3f0(int *pOut, int nCode);
extern void func_ov002_0205c57c(void);
extern void func_ov002_0205bff4(int nKind, int nKindAgain);
extern int func_ov002_020536bc(int nTag);
extern void func_ov002_020536dc(int nEntry, int bArmed);
extern long long func_02020400(int nNumerator, int nDenominator);
extern void func_ov002_0205c624(int nColumn);
extern void func_ov002_0205a924(int nX, int nY, int nW, int nH);
extern int func_ov002_0205a4a0(void);
extern int func_ov002_0205a4ec(void);
extern void func_ov002_0205c6f4(int nCode);
extern void func_ov002_0205c87c(int nColumn);
extern void func_ov002_0205c9c4(void);
extern void func_ov002_0205cab0(void);
extern void func_02033b78(int nBank, int nSound);
extern void func_02033b24(int nBank, int nSound);
extern void func_ov002_0205b7dc(int nCode, int nKind, int nFlag);

void func_ov002_0205d214(int nRaw, int nSound) {
    int nColumn;
    Ov002PanelSession *s = data_ov002_0207f620;
    int nCode;
    int nPrev;

    if (s == 0) {
        return;
    }

    func_ov002_0205cbd0();
    nCode = func_ov002_0205bbbc(nRaw);
    nPrev = func_ov002_0205a3f0(0, s->bMode);

    switch (func_ov002_0205a3f0(&nColumn, nCode)) {
    case 0:
        switch (func_ov002_0205a3f0(0, s->bMode)) {
        case 1:
            s->bKind = 1;
            break;
        case 2:
        case 3:
            s->bKind = 2;
            break;
        case 4:
            s->bKind = 0;
            break;
        }
        func_ov002_0205c57c();
        s->bMode = (u8)nCode;
        func_ov002_0205bff4(s->bKind, s->bKind);
        func_ov002_020536dc(func_ov002_020536bc(2), 1);
        break;

    case 1:
        s->bIndex = (u8)(s->bKind + nColumn * 6);
        if (s->bIndex >= s->bColumns ||
            *(u8 *)((u8 *)s + s->bIndex * 2 + 0x32) == 0xff) {
            s->bIndex = (u8)(s->bColumns - 1);
        }
        s->bKind = (u8)((unsigned long long)func_02020400(s->bIndex, 6) >> 32);
        func_ov002_0205c624(nColumn);
        func_ov002_0205a924(nColumn + 1, s->bRowSpan, 7, 0xb);
        func_ov002_020536dc(func_ov002_020536bc(2), 1);
        break;

    case 2:
        s->bPanelRow = (u8)(s->bKind + nColumn * 6);
        if (func_ov002_0205a4a0() > 0) {
            if (s->bPanelRow >= func_ov002_0205a4a0()) {
                s->bPanelRow = (u8)(func_ov002_0205a4a0() - 1);
            }
        } else {
            if (s->bKey >= func_ov002_0205a4ec()) {
                s->bKey = (u8)(func_ov002_0205a4ec() - 1);
            }
        }
        s->bKind =
            (u8)((unsigned long long)func_02020400(s->bPanelRow, 6) >> 32);
        func_ov002_0205c6f4(nCode);
        func_ov002_0205a924(nColumn + 1,
                            *(u8 *)((u8 *)s + 0x4ac) +
                                *(u8 *)((u8 *)s + 0x4ad),
                            7, 0xb);
        func_ov002_020536dc(func_ov002_020536bc(2), 1);
        break;

    case 3:
        s->bKey = (u8)(s->bKind + nColumn * 6);
        if (s->bKey >= 1 && s->bKey >= func_ov002_0205a4ec()) {
            s->bKey = (u8)(func_ov002_0205a4ec() - 1);
        }
        nColumn = (int)func_02020400(s->bKey, 6);
        s->bKind = (u8)((unsigned long long)func_02020400(s->bKey, 6) >> 32);
        nCode = nColumn + 6;
        func_ov002_0205c87c(nColumn);
        func_ov002_0205a924(*(u8 *)((u8 *)s + 0x4ac) + nColumn + 1,
                            *(u8 *)((u8 *)s + 0x4ac) +
                                *(u8 *)((u8 *)s + 0x4ad),
                            7, 0xb);
        func_ov002_020536dc(func_ov002_020536bc(2), 1);
        break;

    case 4:
        func_ov002_0205c9c4();
        s->bMode = (u8)nCode;
        func_ov002_020536dc(func_ov002_020536bc(2), 0);
        nSound = -1;
        break;

    case 5:
        s->bKind = s->bSpare7;
        func_ov002_0205cab0();
        break;
    }

    if (nPrev != 4 && nSound >= 0) {
        if (nSound <= 7) {
            func_02033b78(0, nSound);
        } else {
            func_02033b24(0, nSound);
        }
    }
    s->bMode = (u8)nCode;
    func_ov002_0205b7dc(nCode, s->bKind, 1);
}
