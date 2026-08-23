/*
 * Ov002_SceneSpawnPanelRowCount - hand the head of the pending queue to one of
 * the ten counter rows.
 *
 * Rows are only handed out on a fixed interval, so the call does nothing until
 * enough ticks have passed since the last one. The row then gets its pair of
 * tweens started - the slide that carries it up and the fade that takes it out
 * - the palette that says whether the number is a gain or a loss, and the value
 * and its sign. The pending queue is shifted down over the entry just consumed,
 * the interval is re-armed from this tick, the row is marked busy and the
 * pending count drops by one.
 *
 * ARM.
 */

typedef unsigned short u16;
typedef unsigned long long u64;

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int dwFlags;
} Ov002Tween;

typedef struct {
    int pad000[21];
    int aQueueSign[10];
    int aRowSign[10];
    int aRowBusy[10];
    char pad0cc[0xa10];
    u16 aRowPalette[10];
    char padaf0[0x38];
    Ov002Tween aRowSlide[10];
    Ov002Tween aRowFade[10];
    char padd58[0x10];
    int aQueueValue[10];
    int aRowValue[10];
    int nPending;
    char paddbc[0x280];
    u64 llStamp;
    u64 llInterval;
} Ov002RowScene;

extern int data_ov002_0207f628;

extern u64 func_020031d4(void);
extern void func_02035fb0(Ov002Tween *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(Ov002Tween *pTween);

void func_ov002_0205fc5c(int nValue, int nSign, int nRow)
{
    int i;
    Ov002RowScene *s;

    s = *(Ov002RowScene **)&data_ov002_0207f628;
    if (func_020031d4() - s->llStamp < s->llInterval) {
        return;
    }

    func_02035fb0(&s->aRowSlide[nRow], 0, 0, 0xbb8000, 1000);
    func_02035ffc(&s->aRowSlide[nRow]);
    func_02035fb0(&s->aRowFade[nRow], 0, 0x1f000, 0, 1000);
    func_02035ffc(&s->aRowFade[nRow]);

    s->aRowPalette[nRow] = (nSign != 0) ? 0x7fc0 : 0x7fff;
    s->aRowValue[nRow] = nValue;
    s->aRowSign[nRow] = nSign;

    for (i = 0; i < 9; i++) {
        s->aQueueValue[i] = s->aQueueValue[i + 1];
        s->aQueueSign[i] = s->aQueueSign[i + 1];
    }

    s->llInterval = 0x3fec4;
    s->aRowBusy[nRow] = 1;
    s->llStamp = func_020031d4();
    s->nPending--;
}
