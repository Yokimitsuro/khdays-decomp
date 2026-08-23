/*
 * Ov002_BuildRunSummary - build the mission summary line and put it on screen.
 *
 * Every part of the run that has something to report adds its own message to a
 * 512-byte buffer, in a fixed order: the time taken, split into minutes and
 * seconds; the combo count; the three bonus flags; the three tallies; and the
 * two closing counts. From the second entry onwards each message is asked to
 * open with the separator, which is what the running flag carries.
 *
 * The finished line is drawn into the summary surface and its width is handed
 * back to the row that owns it.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    char pad000[0x10];
    char textCtx[0x44];
    int nStyle;
} Ov002TextScene;

typedef struct {
    u16 nSeconds;
    u16 nCombo;
    u16 wBonus;
    u8 nTallyA;
    u8 nTallyB;
    u8 nTallyC;
    char pad009[1];
    u16 nExtraA;
    u16 nExtraB;
} Ov002RunStats;

extern int data_ov002_0207f62c;
extern Ov002RunStats data_0204c254;

extern void func_02030094(void *pCtx, int nStyle, int nFlags);
extern void func_02030278(void *pCtx, int a, int b, int c, void *pText, int d);
extern int func_020303bc(void *pCtx, void *pText);

extern void func_ov002_020626cc(void *pSink, unsigned int nId, int bOpen,
                                int nArg, ...);
extern void func_ov002_02062678(void *pSink, unsigned int nId, int bOpen,
                                int nArg);
extern void func_ov002_02057454(int nRow, int nWidth);

void func_ov002_02062748(void)
{
    Ov002TextScene *s = *(Ov002TextScene **)((char *)&data_ov002_0207f62c + 4);
    short aText[0x100] = { 0 };
    int nSeconds = data_0204c254.nSeconds;
    int nMinutes = nSeconds / 60;
    int nRemain = nSeconds % 60;
    int bMore = 0;

    if (nMinutes > 0) {
        func_ov002_020626cc(aText, 2, 0, 0x100, nMinutes);
        bMore = 1;
    }
    if (nRemain > 0) {
        func_ov002_020626cc(aText, 3, 0, 0x100, nRemain);
        bMore = 1;
    }
    if (bMore != 0) {
        func_ov002_02062678(aText, 4, 0, 0x100);
    }

    if (data_0204c254.nCombo != 0) {
        func_ov002_020626cc(aText, 5, bMore, 0x100, data_0204c254.nCombo);
        bMore = 1;
    }
    if ((data_0204c254.wBonus & 1) != 0) {
        func_ov002_02062678(aText, 6, bMore, 0x100);
        bMore = 1;
    }
    if ((data_0204c254.wBonus & 2) != 0) {
        func_ov002_02062678(aText, 7, bMore, 0x100);
        bMore = 1;
    }
    if ((data_0204c254.wBonus & 4) != 0) {
        func_ov002_02062678(aText, 8, bMore, 0x100);
        bMore = 1;
    }
    if (data_0204c254.nTallyA != 0) {
        func_ov002_020626cc(aText, 9, bMore, 0x100, data_0204c254.nTallyA);
        bMore = 1;
    }
    if (data_0204c254.nTallyB != 0) {
        func_ov002_020626cc(aText, 0xa, bMore, 0x100, data_0204c254.nTallyB);
        bMore = 1;
    }
    if (data_0204c254.nTallyC != 0) {
        func_ov002_020626cc(aText, 0xb, bMore, 0x100, data_0204c254.nTallyC);
        bMore = 1;
    }
    if (data_0204c254.nExtraA != 0) {
        func_ov002_02062678(aText, 0xc, bMore, 0x100);
        bMore = 1;
    }
    if (data_0204c254.nExtraB != 0) {
        func_ov002_020626cc(aText, 0xd, bMore, 0x100);
    }

    func_02030094(s->textCtx, s->nStyle, 0);
    func_02030278(s->textCtx, 8, 3, 0xc, aText, 0);
    func_ov002_02057454(1, func_020303bc(s->textCtx, aText));
    func_02030094(s->textCtx, 0, 0);
}
