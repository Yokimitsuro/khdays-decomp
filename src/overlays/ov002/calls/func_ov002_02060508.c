/*
 * Ov002_SceneStepPanelCounters - move the panel's running total one step
 * towards its target and hand out any queued row counters.
 *
 * The step is one plus a twentieth of the distance left, signed by the direction
 * of travel, so the total sprints while it is far away and crawls at the end. What
 * happens next depends on the state word: at 0 the total is resting and only
 * moves once the step interval has passed, at 1 it is already moving, and at 2
 * it is snapped straight onto its target.
 *
 * Any row that is free then takes the head of the pending queue, provided the
 * queue has not overflowed. Finally, while the total is still short of its
 * target and its tint tween is free, that tween is restarted - brighter the
 * bigger the step - along with the flash and, unless this step lands on the
 * target, the depth tween. The step is only applied when the tween was free, so
 * the total advances at the speed of its own animation.
 *
 * ARM.
 */

typedef unsigned long long u64;

typedef struct {
    int nMode;
    int nDuration;
    int nFrom;
    int nTo;
    int aStart[2];
    unsigned int pad0 : 2;
    unsigned int bFree : 1;
} Ov002Tween;

typedef struct {
    int aTint[3];
} Ov002StepTints;

typedef struct {
    char pad000[0x44];
    int bDim;
    char pad048[4];
    int bClick;
    char pad050[4];
    int aQueueSign[10];
    char pad07c[0x28];
    int aRowBusy[10];
    char pad0cc[0x688];
    Ov002Tween aFlash[4];
    char pad7c4[0x32c];
    Ov002Tween tweenTint;
    Ov002Tween tweenDepth;
    char padb28[0x230];
    int nCounterState;
    char padd5c[4];
    int nTotalShown;
    int nTotalTarget;
    int aQueueValue[10];
    char padd90[0x28];
    int nPending;
    char paddbc[0x270];
    u64 llStepStamp;
    u64 llStepInterval;
} Ov002StepScene;

extern int data_ov002_0207f628;
extern const Ov002StepTints data_ov002_0207e190;

extern u64 func_020031d4(void);
extern void func_02035fb0(Ov002Tween *pTween, int nMode, int nFrom, int nTo,
                          int nDuration);
extern void func_02035ffc(Ov002Tween *pTween);

extern void func_ov002_0205f980(void);
extern void func_ov002_0205f9a8(void);
extern void func_ov002_0205fc5c(int nValue, int nSign, int nRow);

void func_ov002_02060508(void)
{
    Ov002StepTints tints;
    u64 llDelta;
    int nDir;
    int nStep;
    int nGap;
    int nDuration;
    int nIndex;
    int i;
    Ov002StepScene *s;

    s = *(Ov002StepScene **)&data_ov002_0207f628;
    nDir = 1;
    nGap = s->nTotalShown - s->nTotalTarget;
    llDelta = func_020031d4() - s->llStepStamp;
    if (nGap < 0) {
        nGap = nGap * 0xffffffff;
    }
    if (s->nTotalShown < s->nTotalTarget) {
        nDir = 1;
    } else if (s->nTotalShown > s->nTotalTarget) {
        nDir = -1;
    }
    nStep = nDir + (s->nTotalTarget - s->nTotalShown) / 20;

    switch (s->nCounterState) {
    case 0:
        if (s->bDim != 0) {
            s->bDim = 0;
        }
        if (llDelta < s->llStepInterval) {
            return;
        }
        if (s->bClick != 0) {
            if (llDelta >= s->llStepInterval) {
                func_ov002_0205f980();
            }
        }
        break;
    case 1:
        if (s->bDim == 0) {
            s->bDim = 1;
        }
        if (s->bClick != 0) {
            func_ov002_0205f980();
        }
        break;
    case 2:
        s->nTotalShown = s->nTotalTarget;
        s->nCounterState = 0;
        break;
    }

    if (s->bClick != 0) {
        s->bClick = 0;
    }

    if (s->nPending > 0) {
        for (i = 0; i < 10; i++) {
            if (s->aRowBusy[i] == 0 && s->nPending <= 10) {
                func_ov002_0205fc5c(s->aQueueValue[0], s->aQueueSign[0], i);
            }
        }
    }

    if (s->nTotalShown < s->nTotalTarget) {
        nDuration = 100 - nGap;
        if (nDuration < 30) {
            nDuration = 30;
        }
        if (s->tweenTint.bFree != 0) {
            tints = data_ov002_0207e190;
            nIndex = 0;
            if (nStep > 1) {
                nIndex = 1;
            }
            if (nStep > 2) {
                nIndex = 2;
            }
            func_02035fb0(&s->tweenTint, 0, tints.aTint[nIndex], 0x5ec,
                          nDuration);
            func_02035ffc(&s->tweenTint);

            if (s->aFlash[0].bFree != 0) {
                func_02035fb0(&s->aFlash[0], 3, 0xd71, 0x119a, 150);
                func_02035ffc(&s->aFlash[0]);
            }
            if (s->nTotalShown + nStep < s->nTotalTarget) {
                func_02035fb0(&s->tweenDepth, 0, 0x1f000, 0x10000, nDuration);
                func_02035ffc(&s->tweenDepth);
            }
            s->nTotalShown += nStep;
        }
        s->nCounterState = 1;
    } else {
        s->nCounterState = 0;
    }
    func_ov002_0205f9a8();
}
