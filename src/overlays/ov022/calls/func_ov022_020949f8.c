/* ov022: push the actor's position into the run's sequence entries and redraw.
 *
 * Only runs for an actor that is currently suppressed and whose second flag word
 * does not carry the "hold" bit. The aimed entry is fed and stepped whenever the
 * run carries its aimed flag; the main entry is fed and stepped unless it has
 * already been marked done, and around that step the shared channel is switched
 * to 3, briefly to 0 for a handful of actor kinds, and back to 3. A run in stage
 * 1 also feeds and steps the third entry.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

struct Vec3 {
    int x, y, z;
};

struct Sequence {
    u16 nFlags;                  /* 0x0000 */
    short nMode;                 /* 0x0002 */
};

struct Actor {
    u8 pad0000[0xc];
    int nKind;                   /* 0x000c */
    u8 pad0010[0x454];
    u64 nFlags2;                 /* 0x0464 */
    u8 pad046c[0x228];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 nFlags694Top : 7;
};

struct Run {
    u32 nFlags;                  /* 0x0000 */
    u8 pad0004[4];
    int nStage;                  /* 0x0008 */
    struct Sequence seqMain;     /* 0x000c */
    u8 pad0010[0x74];
    void *pChannel;              /* 0x0084 */
    u8 pad0088[0x28];
    struct Vec3 vecMain;         /* 0x00b0 */
    u8 pad00bc[0x58];
    struct Sequence seqAimed;    /* 0x0114 */
    u8 pad0118[0xa0];
    struct Vec3 vecAimed;        /* 0x01b8 */
    u8 pad01c4[0x58];
    struct Sequence seqThird;    /* 0x021c */
    u8 pad0220[0xa0];
    struct Vec3 vecThird;        /* 0x02c0 */
    u8 pad02cc[0x5c];
    struct Actor *pActor;        /* 0x0328 */
};

extern void func_ov022_020ad44c(struct Vec3 *pOut, struct Actor *pActor);
extern void func_0202aa9c(struct Sequence *pSeq);
extern void func_02016ae8(void *pChannel, int nWhich, int nValue);

void func_ov022_020949f8(struct Run *pRun)
{
    struct Vec3 vecFeed;
    struct Vec3 vecPos;
    struct Actor *pActor;

    func_ov022_020ad44c(&vecPos, pRun->pActor);
    vecFeed = vecPos;
    pActor = pRun->pActor;
    if (pActor->bSuppressDraw == 0) {
        return;
    }
    if ((pActor->nFlags2 & 0x200000000ULL) != 0) {
        return;
    }
    if ((pRun->nFlags & 0x200) != 0) {
        pRun->vecAimed = vecFeed;
        func_0202aa9c(&pRun->seqAimed);
    }
    if ((pRun->seqMain.nFlags & 2) == 0) {
        pRun->vecMain = vecFeed;
        func_02016ae8(pRun->pChannel, 7, 3);
        switch (pActor->nKind) {
        case 5:
        case 0xb:
        case 0x10:
        case 0x11:
        case 0x12:
            func_02016ae8(pRun->pChannel, 7, 0);
            break;
        }
        func_0202aa9c(&pRun->seqMain);
        func_02016ae8(pRun->pChannel, 7, 3);
    }
    if (pRun->nStage != 1) {
        return;
    }
    pRun->vecThird = vecFeed;
    func_0202aa9c(&pRun->seqThird);
}
