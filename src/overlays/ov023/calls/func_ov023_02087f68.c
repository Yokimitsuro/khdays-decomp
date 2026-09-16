/* func_ov023_02087f68 -- Ov023_ActorPopMotion: start the motion at the head of a track's queue
 * (Ov023_ActorStartMotion 02087298 on the actor's motion set, +0x538: five queue depths of
 * five tracks, 0x2c bytes each) and pop the queue: the head is cleared (frame -1, empty name)
 * and every queued entry behind it moves one depth up (frame, blend, name) until an empty
 * one. */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct Ov023Motion {
    int  nField00;            /* 0x00 */
    s16  nFrame;              /* 0x04 */
    u8   pad_06[2];
    int  nBlend;              /* 0x08 */
    char szName[0x20];        /* 0x0c */
} Ov023Motion;                /* 0x2c */

typedef struct Ov023Actor {
    u8   pad_0000[0x538];
    Ov023Motion aMotion[5][5]; /* 0x0538: [depth][track] */
} Ov023Actor;

extern void func_ov023_02087298(Ov023Actor *pActor, int nTrack);  /* Ov023_ActorStartMotion */
extern void func_0201f924(char *pszDst, const char *pszSrc);       /* STD_CopyString */

void func_ov023_02087f68(Ov023Actor *pActor, int nTrack)
{
    Ov023Motion *pHead;
    int i;

    pHead = &pActor->aMotion[0][nTrack];
    func_ov023_02087298(pActor, nTrack);
    pHead->nFrame = -1;
    pHead->szName[0] = 0;
    for (i = 1; i < 5; i++) {
        if (pActor->aMotion[i][nTrack].nFrame == -1) {
            return;
        }
        pActor->aMotion[i - 1][nTrack].nFrame = pActor->aMotion[i][nTrack].nFrame;
        pActor->aMotion[i - 1][nTrack].nBlend = pActor->aMotion[i][nTrack].nBlend;
        func_0201f924(pActor->aMotion[i - 1][nTrack].szName, pActor->aMotion[i][nTrack].szName);
        pActor->aMotion[i][nTrack].nFrame = -1;
        pActor->aMotion[i][nTrack].szName[0] = 0;
    }
}
