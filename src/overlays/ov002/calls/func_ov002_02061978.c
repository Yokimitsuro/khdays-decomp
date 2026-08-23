/*
 * Ov002_AddToPanelTotal - move the panel's target total and queue the numbers
 * that say why.
 *
 * Nothing happens without a scene, while the counter is switched off, or when
 * the two amounts cancel out. The new target is clamped to 0..cap.
 *
 * When the caller wants the change shown, each non-zero amount is queued as its
 * own row - the first with the loss palette, the second with the gain one - as
 * long as the queue has room. When the caller does not, the counter is snapped
 * onto the new target instead.
 *
 * Either way the step interval is stretched to a second from now and the click
 * is armed.
 *
 * ARM.
 */

typedef unsigned long long u64;

typedef struct {
    char pad000[0x4c];
    int bClick;
    char pad050[4];
    int aQueueSign[10];
    char pad07c[0xcdc];
    int nCounterState;
    char padd5c[8];
    int nTotalTarget;
    int aQueueValue[10];
    char padd90[0x28];
    int nPending;
    char paddbc[0x270];
    u64 llStepStamp;
    u64 llStepInterval;
} Ov002QueueScene;

extern int data_ov002_0207f628;

extern u64 func_020031d4(void);

extern int func_ov002_0206189c(int nKind);

void func_ov002_02061978(int nLoss, int nGain, int bShow)
{
    int nCap;
    int nTarget;
    int nValue;
    Ov002QueueScene *s;

    s = *(Ov002QueueScene **)&data_ov002_0207f628;
    if (s == 0) {
        return;
    }
    nCap = func_ov002_0206189c(4);
    if (s->nCounterState == -1) {
        return;
    }

    nTarget = s->nTotalTarget + (nLoss + nGain);
    if (nTarget == s->nTotalTarget) {
        return;
    }
    if (nTarget < 0) {
        nTarget = 0;
    }
    if (nTarget > nCap) {
        nTarget = nCap;
    }
    s->nTotalTarget = nTarget;

    if (bShow == 0) {
        s->nCounterState = 2;
    }

    if (bShow != 0) {
        if (nLoss > 0 && s->nPending < 10) {
            nValue = -nLoss;
            if (nValue < 0) {
                nValue = nValue * 0xffffffff;
            }
            s->aQueueValue[s->nPending] = nValue;
            s->aQueueSign[s->nPending] = 0;
            s->nPending++;
        }
        if (nGain > 0 && s->nPending < 10) {
            s->aQueueValue[s->nPending] = nGain;
            s->aQueueSign[s->nPending] = 1;
            s->nPending++;
        }
    }

    if (bShow == 0) {
        s->nCounterState = 2;
    }

    s->llStepInterval = 0x7fd88;
    s->llStepStamp = func_020031d4();
    s->bClick = 1;
}
