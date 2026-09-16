/* func_ov023_0208929c -- Ov023_ActorQueueSound: queue a sound request on an actor, alongside
 * the first queued motion: the queue depths (+0x538, 0xdc each) are searched for the first
 * whose track-0 entry holds a motion (frame not -1) and that depth's two 0x10-byte sound
 * requests (+0x498, 0x20 per depth) get the first free one (kind 0) filled with the pair,
 * the kind and the extra word. */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct Ov023SoundRequest {
    int  nA;                  /* 0x00 */
    int  nB;                  /* 0x04 */
    int  nC;                  /* 0x08 */
    int  nKind;               /* 0x0c */
} Ov023SoundRequest;          /* 0x10 */

typedef struct Ov023Motion {
    int  nEndFrame;           /* 0x00 */
    s16  nFrame;              /* 0x04 */
    u8   pad_06[2];
    int  nBlend;              /* 0x08 */
    char szName[0x20];        /* 0x0c */
} Ov023Motion;                /* 0x2c */

typedef struct Ov023Actor {
    u8   pad_0000[0x498];
    Ov023SoundRequest aSound[5][2]; /* 0x0498: [depth][slot] */
    Ov023Motion aMotion[5][5]; /* 0x0538: [depth][track] */
} Ov023Actor;

void func_ov023_0208929c(Ov023Actor *pActor, int nA, int nB, int nKind, int nC)
{
    int i;
    int j;

    for (i = 0; i < 5; i++) {
        if (pActor->aMotion[i][0].nFrame == -1) {
            continue;
        }
        for (j = 0; j < 2; j++) {
            if (pActor->aSound[i][j].nKind == 0) {
                pActor->aSound[i][j].nA = nA;
                pActor->aSound[i][j].nB = nB;
                pActor->aSound[i][j].nKind = nKind;
                pActor->aSound[i][j].nC = nC;
                return;
            }
        }
        return;
    }
}
