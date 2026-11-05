/* ov022: step one run's sequences for this frame.
 *
 * Takes the actor's current position once and hands the same copy to every
 * sequence that wants it. The main sequence always advances, and is re-enabled
 * whenever it reports work done. While the run carries its "aimed" flag the
 * alternate sequence advances too, and what happens next depends on its mode:
 * mode 0 asks whether the slot is ready before switching to channel set 1,
 * mode 1 switches to set 2 as soon as the sequence itself reports done, and
 * mode 2 just advances.
 *
 * Once the run has passed its timeout the main sequence is rewound, disabled and
 * the actor plays its give-up voice, and that only happens once because the same
 * test raises the bit it checks. Finally, a run in stage 1 also feeds the third
 * sequence.
 */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

struct Sequence {
    u16 nFlags;                  /* 0x0000 */
    short nMode;                 /* 0x0002 */
};

struct Actor;

struct Run {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[4];
    int nStage;                  /* 0x0008 */
    struct Sequence seqMain;     /* 0x000c */
    u8 pad0010[0x104];
    struct Sequence seqAimed;    /* 0x0114 */
    u8 pad0118[0xa0];
    VecFx32 vecAimed;        /* 0x01b8 */
    u8 pad01c4[0x58];
    struct Sequence seqThird;    /* 0x021c */
    u8 pad0220[0xa0];
    VecFx32 vecThird;        /* 0x02c0 */
    u8 pad02cc[0x5c];
    struct Actor *pActor;        /* 0x0328 */
    u8 pad032c[4];
    int nElapsed;                /* 0x0330 */
};

extern void func_ov022_020ad44c(VecFx32 *pOut, struct Actor *pActor);
extern unsigned short Sequence_UpdateTracks(struct Sequence *pSeq, int nDelta);
extern void Anim_SetFrameWrapped(struct Sequence *pSeq, int nWhich, int nFrame);
extern int Ov022_IsSlotReady(struct Run *pRun);
extern void func_ov022_02094b80(struct Run *pRun, int nSet);
extern void Ov022_PlayEntityVoice(struct Actor *pActor, int nSeqArc, int nSeq);

void Ov022_StepRunSequences(struct Run *pRun, int nDelta)
{
    VecFx32 vecFeed;
    VecFx32 vecPos;
    struct Actor *pActor;

    pActor = pRun->pActor;
    func_ov022_020ad44c(&vecPos, pActor);
    vecFeed = vecPos;
    if (Sequence_UpdateTracks(&pRun->seqMain, nDelta) != 0) {
        SceneNode_Enable(&pRun->seqMain);
    }
    if ((pRun->nFlags & 0x200) != 0) {
        pRun->vecAimed = vecFeed;
        switch (pRun->seqAimed.nMode) {
        case 0:
            Sequence_UpdateTracks(&pRun->seqAimed, nDelta);
            if (Ov022_IsSlotReady(pRun) != 0) {
                func_ov022_02094b80(pRun, 1);
            }
            break;
        case 1:
            if (Sequence_UpdateTracks(&pRun->seqAimed, nDelta) != 0) {
                func_ov022_02094b80(pRun, 2);
            }
            break;
        case 2:
            Sequence_UpdateTracks(&pRun->seqAimed, nDelta);
            break;
        }
    }
    if ((pRun->nFlags & 0x40) == 0 && (pRun->nFlags & 0x100) != 0
        && pRun->nElapsed > 0x1000) {
        pRun->nFlags |= 0x40;
        Anim_SetFrameWrapped(&pRun->seqMain, 0, 0);
        Anim_SetFrameWrapped(&pRun->seqMain, 2, 0);
        SceneNode_Disable(&pRun->seqMain);
        Ov022_PlayEntityVoice(pActor, 0, 0x47);
    }
    if (pRun->nStage != 1) {
        return;
    }
    pRun->vecThird = vecFeed;
    Sequence_UpdateTracks(&pRun->seqThird, nDelta);
}
