/* ov022: give the actor a sequence and bind its three animation tracks.
 *
 * Only while the scene flag that gates this whole path is up; without it the
 * actor keeps whatever it already had.
 *
 * The sequence is registered from the descriptor the caller names, enabled and
 * under one fixed class. Its three tracks are then bound at the even slots
 * against the actor's own track block.
 *
 * Afterwards the track count is zeroed and the running flag comes down, so the
 * sequence starts from nothing rather than from whatever the last one left.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

#define SCENE_BIT 4
#define SEQ_ENABLED 1
#define SEQ_CLASS 5

struct Actor;

extern u8 data_0204c240;

/* RegisterSeqAndInit */
extern void func_0202a634(void *pSequence, const char *pszDescriptor,
                          int bEnabled, int nClassId);
/* BindAnimTrack */
extern void func_0202accc(void *pSequence, int nSlot, void *pTrack,
                          int nArg);

/* Ov022Actor */
struct ActorBody {
    u8 pad0000[0x694];
    u8 bSuppressDraw : 1;        /* 0x0694 bit 0 */
    u8 bStateOver : 1;           /* bit 1 */
    u8 nSpare694 : 1;
    u8 bActionLocked : 1;        /* bit 3 */
    u8 bSequenceRunning : 1;     /* bit 4 */
    u8 nFlags694Top : 3;
    u8 pad0695[0x13f];
    u8 seqBlk;                   /* 0x07d4 */
    u8 pad07d5[0xdf];
    u8 trackBlk;                 /* 0x08b4 */
    u8 pad08b5[0x27];
    u16 nTrackCount;             /* 0x08dc */
};

void func_ov022_0209d1d8(struct ActorBody *pActor, const char *pszDescriptor)
{
    if ((data_0204c240 & SCENE_BIT) == 0) {
        return;
    }
    func_0202a634(&pActor->seqBlk, pszDescriptor, SEQ_ENABLED, SEQ_CLASS);
    func_0202accc(&pActor->seqBlk, 0, &pActor->trackBlk, 0);
    func_0202accc(&pActor->seqBlk, 2, &pActor->trackBlk, 0);
    func_0202accc(&pActor->seqBlk, 4, &pActor->trackBlk, 0);
    pActor->nTrackCount = 0;
    pActor->bSequenceRunning = 0;
}
