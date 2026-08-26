/*
 * Ov002_SceneStepPanelRowFx - run the three-step flash of each of the three
 * moving widgets the panel carries.
 *
 * Every widget has its own step counter and its own set of three tweens. The
 * counter is clamped back to 0 once it walks past the last step, and a widget
 * sitting at 0 is left alone. Otherwise each of its tweens that has finished
 * takes the leg of its own track for the current step; only the level tween
 * advances the counter, so the other two follow it through the same leg.
 *
 * All three tweens are sampled every pass. The level one becomes the widget's
 * element index and the slide one its X offset; the middle sample is read but
 * not used. The first widget is tinted apart from the other two.
 *
 * Two details of the shape are load-bearing rather than stylistic. Each track set
 * is walked through a row pointer of its own instead of being indexed by the
 * counter: the three pointers are what make the row addresses live in registers
 * across the sampling calls, and the level one is the row the allocator ends up
 * keeping on the stack. And the element store sits between the tween advances and
 * the row advances because that is where its widget's index is final - the tweens
 * for this pass are done with, the rows are not yet moved on.
 *
 * ARM.
 */

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int pad0 : 2;
    unsigned int bDone : 1;
} Ov002Tween;

typedef struct {
    int nFrom;
    int nTo;
    short nDuration;
} Ov002FxStep;

typedef struct {
    Ov002FxStep aStep[3];
} Ov002FxTrack;

typedef struct {
    Ov002FxTrack aRow[3];
} Ov002FxTrackSet;

typedef struct {
    int x;
    int y;
    int z;
} Ov002Vec3;

typedef struct {
    char pad000[0x718];
    Ov002Vec3 pos;
} Ov002RowView;

typedef struct {
    char pad000[0x718];
    Ov002Vec3 aRowPos[3];
    int aRowTint[3];
    int aRowElem[3];
    char pad754[0x74];
    Ov002Tween aRowFx[3][3];
    short aRowStep[3];
} Ov002RowFxScene;

extern int data_ov002_0207f628;
extern const Ov002FxTrackSet data_ov002_0207e214;
extern const Ov002FxTrackSet data_ov002_0207e280;
extern const Ov002FxTrackSet data_ov002_0207e2ec;

extern void func_02035fb0(Ov002Tween *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(Ov002Tween *pTween);
extern void func_0203602c(Ov002Tween *pTween, int *pOut);

void func_ov002_0205ffd4(void)
{
    Ov002RowFxScene *b;
    int nUnused = 0;
    int nElem = 0;
    int nSlide = 0;
    int i;
    int nStep;
    Ov002Tween *pLevel;
    Ov002Tween *pTint;
    Ov002Tween *pSlide;
    Ov002FxTrack *pLevelRow;
    Ov002FxTrack *pTintRow;
    Ov002FxTrack *pSlideRow;
    Ov002Vec3 *pPos;
    Ov002RowFxScene *s = *(Ov002RowFxScene **)&data_ov002_0207f628;
    b = s;
    Ov002FxTrackSet level = data_ov002_0207e214;
    Ov002FxTrackSet tint = data_ov002_0207e280;
    Ov002FxTrackSet slide = data_ov002_0207e2ec;

    pLevel = &s->aRowFx[2][0];
    pTint = &s->aRowFx[1][0];
    pSlide = &s->aRowFx[0][0];
    pLevelRow = level.aRow;
    pTintRow = tint.aRow;
    pSlideRow = slide.aRow;
    for (i = 0; i < 3; i++) {
        nStep = b->aRowStep[i] - 1;
        if (nStep >= 3) {
            b->aRowStep[i] = 0;
        }
        if (b->aRowStep[i] > 0) {
            if (pLevel->bDone != 0) {
                func_02035fb0(pLevel, 0,
                              pLevelRow->aStep[nStep].nFrom,
                              pLevelRow->aStep[nStep].nTo,
                              pLevelRow->aStep[nStep].nDuration);
                func_02035ffc(pLevel);
                b->aRowStep[i]++;
            }
            if (pTint->bDone != 0) {
                func_02035fb0(pTint, 0,
                              pTintRow->aStep[nStep].nFrom,
                              pTintRow->aStep[nStep].nTo,
                              pTintRow->aStep[nStep].nDuration);
                func_02035ffc(pTint);
            }
            if (pSlide->bDone != 0) {
                func_02035fb0(pSlide, 0,
                              pSlideRow->aStep[nStep].nFrom,
                              pSlideRow->aStep[nStep].nTo,
                              pSlideRow->aStep[nStep].nDuration);
                func_02035ffc(pSlide);
            }
        }

        func_0203602c(pTint, &nUnused);
        func_0203602c(pLevel, &nElem);
        func_0203602c(pSlide, &nSlide);

        pPos = &((Ov002RowView *)s)->pos;
        b->aRowTint[i] = (i == 0) ? 0x5ec : 0x75c;
        pPos->x = nSlide >> 12;
        pPos->y = 0x3520;
        pPos->z = 0;
        pLevel++;
        pTint++;
        b->aRowElem[i] = nElem >> 12;
        pLevelRow++;
        pTintRow++;
        pSlide++;
        pSlideRow++;
        s = (Ov002RowFxScene *)((char *)s + 0xc);
    }
}
