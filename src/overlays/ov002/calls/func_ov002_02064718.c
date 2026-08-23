/*
 * Ov002_SetPageMarkTarget - aim the mark at a new value and let it walk there.
 *
 * The target is where the value sits on the twenty-eight cell ruler. How long
 * each step takes falls with the distance still to go - twenty-five steps for a
 * standing start, two at the far end - and the step time is kept beside the
 * timestamp the walk starts from.
 *
 * When the caller asks for it and the mark really has ground to make up, the
 * walk is started and the mark is flagged as moving.
 *
 * ARM.
 */

typedef struct {
    int nTotal;
} Ov002PageProgress;

typedef struct {
    int nCurrent;
    int nTarget;
    int bMoving;
    char pad00c[4];
    unsigned long long llStamp;
    unsigned long long llStep;
} Ov002PageMark;

extern int data_ov002_0207f634;

extern long long func_02020400(int nNumerator, int nDenominator);
extern unsigned long long func_020031d4(void);
extern void func_02033b24(int a, int b);

extern int func_ov002_02063698(void);
extern int func_ov002_020636ac(void);

void func_ov002_02064718(int nValue, int bStart)
{
    int nCtx;
    Ov002PageProgress *p;
    Ov002PageMark *m;
    int nSteps;

    nCtx = data_ov002_0207f634;
    p = (Ov002PageProgress *)func_ov002_02063698();
    m = (Ov002PageMark *)func_ov002_020636ac();
    if (nCtx == 0) {
        return;
    }

    m->llStamp = func_020031d4();
    m->nTarget = (int)func_02020400(nValue * 0xe0, p->nTotal);
    nSteps = 0x19 - (m->nTarget - m->nCurrent) * 0x19 / 0xe0;
    if (nSteps > 0x19) {
        nSteps = 0x19;
    } else if (nSteps < 2) {
        nSteps = 2;
    }
    m->llStep = (unsigned long long)nSteps * 0x82ea >> 6;

    if (bStart != 0 && m->nTarget > m->nCurrent && m->bMoving == 0) {
        func_02033b24(0, 0x32);
        m->bMoving = 1;
    }
}
