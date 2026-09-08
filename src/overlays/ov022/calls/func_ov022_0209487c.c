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

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Vec3 {
    int x, y, z;
};

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
    struct Vec3 vecAimed;        /* 0x01b8 */
    u8 pad01c4[0x58];
    struct Sequence seqThird;    /* 0x021c */
    u8 pad0220[0xa0];
    struct Vec3 vecThird;        /* 0x02c0 */
    u8 pad02cc[0x5c];
    struct Actor *pActor;        /* 0x0328 */
    u8 pad032c[4];
    int nElapsed;                /* 0x0330 */
};

extern void func_ov022_020ad44c(struct Vec3 *pOut, struct Actor *pActor);
extern int func_0202a818(struct Sequence *pSeq, int nDelta);
extern void func_0202af1c(struct Sequence *pSeq);
extern void func_0202af2c(struct Sequence *pSeq);
extern void func_01fff774(struct Sequence *pSeq, int nWhich, int nFrame);
extern int func_ov022_02095554(struct Run *pRun);
extern void func_ov022_02094b80(struct Run *pRun, int nSet);
extern void func_ov022_020a4490(struct Actor *pActor, int nA, int nCue);

void func_ov022_0209487c(struct Run *pRun, int nDelta)
{
    struct Vec3 vecFeed;
    struct Vec3 vecPos;
    struct Actor *pActor;

    pActor = pRun->pActor;
    func_ov022_020ad44c(&vecPos, pActor);
    vecFeed = vecPos;
    if (func_0202a818(&pRun->seqMain, nDelta) != 0) {
        func_0202af1c(&pRun->seqMain);
    }
    if ((pRun->nFlags & 0x200) != 0) {
        pRun->vecAimed = vecFeed;
        switch (pRun->seqAimed.nMode) {
        case 0:
            func_0202a818(&pRun->seqAimed, nDelta);
            if (func_ov022_02095554(pRun) != 0) {
                func_ov022_02094b80(pRun, 1);
            }
            break;
        case 1:
            if (func_0202a818(&pRun->seqAimed, nDelta) != 0) {
                func_ov022_02094b80(pRun, 2);
            }
            break;
        case 2:
            func_0202a818(&pRun->seqAimed, nDelta);
            break;
        }
    }
    if ((pRun->nFlags & 0x40) == 0 && (pRun->nFlags & 0x100) != 0
        && pRun->nElapsed > 0x1000) {
        pRun->nFlags |= 0x40;
        func_01fff774(&pRun->seqMain, 0, 0);
        func_01fff774(&pRun->seqMain, 2, 0);
        func_0202af2c(&pRun->seqMain);
        func_ov022_020a4490(pActor, 0, 0x47);
    }
    if (pRun->nStage != 1) {
        return;
    }
    pRun->vecThird = vecFeed;
    func_0202a818(&pRun->seqThird, nDelta);
}
