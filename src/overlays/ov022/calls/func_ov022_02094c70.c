/* ov022: start a run for one actor.
 *
 * Binds the three sequence entries to the shared track set, wires each of their
 * three channels to that entry's own block with the entry's own group number,
 * enables the main entry, clears the run's stage, links the actor and copies the
 * actor's cue out of the per-id table. While the session is up the cue is
 * applied straight away.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Actor {
    u8 pad0000[9];
    u8 nId;                      /* 0x0009 */
};

struct Sequence {
    u16 nFlags;                  /* 0x0000 */
    short nMode;                 /* 0x0002 */
    u8 pad0004[0xdc];
    u8 blkChannels;              /* 0x00e0 */
    u8 pad00e1[0x27];
};

struct Run {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[4];
    int nStage;                  /* 0x0008 */
    struct Sequence aSequences[3];  /* 0x000c */
    int nSpare324;               /* 0x0324 */
    struct Actor *pActor;        /* 0x0328 */
    u8 pad032c[9];
    u8 nCue;                     /* 0x0335 */
};

extern u8 data_ov022_020b2c50;
/* Per-id table of 0x44-byte records; only the cue byte matters here. */
struct Record {
    u8 pad0000[0x33];
    s8 nCue;                     /* 0x0033 */
    u8 pad0034[0x10];
};

extern struct Record data_0204c3d8[];

extern void func_0202a634(struct Sequence *pSeq, u8 *pTracks, int nA, int nB);
extern void func_0202accc(struct Sequence *pSeq, int nChannel, u8 *pBlk,
                          int nGroup);
extern void func_0202af1c(struct Sequence *pSeq);
extern int func_02030694(void);
extern void func_ov022_02094810(struct Run *pRun, int nCue);

void func_ov022_02094c70(struct Run *pRun, struct Actor *pActor)
{
    struct Record *pRec;

    func_0202a634(&pRun->aSequences[0], &data_ov022_020b2c50, 1, 5);
    func_0202a634(&pRun->aSequences[1], &data_ov022_020b2c50, 1, 5);
    func_0202a634(&pRun->aSequences[2], &data_ov022_020b2c50, 1, 5);
    func_0202accc(&pRun->aSequences[0], 0, &pRun->aSequences[0].blkChannels, 3);
    func_0202accc(&pRun->aSequences[0], 2, &pRun->aSequences[0].blkChannels, 3);
    func_0202accc(&pRun->aSequences[0], 1, &pRun->aSequences[0].blkChannels, 3);
    func_0202af1c(&pRun->aSequences[0]);
    func_0202accc(&pRun->aSequences[1], 0, &pRun->aSequences[1].blkChannels, 0);
    func_0202accc(&pRun->aSequences[1], 2, &pRun->aSequences[1].blkChannels, 0);
    func_0202accc(&pRun->aSequences[1], 1, &pRun->aSequences[1].blkChannels, 0);
    func_0202accc(&pRun->aSequences[2], 0, &pRun->aSequences[2].blkChannels, 4);
    func_0202accc(&pRun->aSequences[2], 2, &pRun->aSequences[2].blkChannels, 4);
    func_0202accc(&pRun->aSequences[2], 1, &pRun->aSequences[2].blkChannels, 4);
    pRun->nStage = 0;
    pRun->nSpare324 = 0;
    pRun->nFlags |= 1;
    pRun->pActor = pActor;
    pRec = &data_0204c3d8[pActor->nId];
    pRun->nCue = pRec->nCue;
    if (func_02030694() != 0) {
        func_ov022_02094810(pRun, pRun->nCue);
    }
}
