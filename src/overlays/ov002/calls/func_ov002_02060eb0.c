#pragma opt_strength_reduction off
/*
 * Ov002_DrawMarkerQueue - draw the numbers still queued over the local player.
 *
 * The three marker slots are a ring: nMarkerHead names the oldest, and only the
 * slots that carry a value count. Each of those is drawn, stacked upwards so
 * the oldest sits highest, faded by its own tween - a slot whose tween has run
 * out is skipped rather than drawn.
 *
 * A second pass retires the first slot whose tween has finished: its value is
 * cleared and the ring head moves on. Only one slot is retired per call.
 *
 * ARM. Strength reduction is off: nothing in this function walks a pointer, and
 * with it on mwcc turns the ring index of the retire pass into its own induction
 * variable. The draw pass reuses the counter of the counting pass, which is what
 * puts the ring index in the lower of the two registers.
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
    char pad000[0x11b0];
    Ov002Tween aMarkerTween[3];
    int aMarkerValue[3];
    int nMarkerHead;
} Ov002MarkerScene;

extern int data_ov002_0207f628;

extern void func_0203602c(Ov002Tween *pTween, int *pOut);

extern void func_ov002_02060d50(int nArg, int nValue, int nAlpha, int nLift);

void func_ov002_02060eb0(int nArg)
{
    int nHead;
    Ov002MarkerScene *s;
    int i;
    int nSample;
    int nCount;
    Ov002Tween *pTween;
    int k;
    int j;

    s = *(Ov002MarkerScene **)&data_ov002_0207f628;
    nCount = 0;
    for (i = 0; i < 3; i++) {
        if (s->aMarkerValue[i] != 0) {
            nCount++;
        }
    }

    for (i = 0; i < nCount; i++) {
        k = (s->nMarkerHead + i) % 3;
        pTween = &s->aMarkerTween[k];
        if (pTween->bDone == 0) {
            func_0203602c(pTween, &nSample);
            func_ov002_02060d50(nArg, s->aMarkerValue[k], nSample,
                                (nCount - i - 1) * 0xa000);
        }
    }

    nHead = s->nMarkerHead;
    for (j = 0; j < nCount; j++) {
        k = (nHead + j) % 3;
        if (s->aMarkerTween[k].bDone != 0) {
            s->aMarkerValue[k] = 0;
            s->nMarkerHead = (s->nMarkerHead + 1) % 3;
            return;
        }
    }
}
