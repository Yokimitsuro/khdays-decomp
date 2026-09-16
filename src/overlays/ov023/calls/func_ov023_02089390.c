/* func_ov023_02089390 -- Ov023_ActorPlayMotion: play a motion on one of an actor's tracks,
 * replacing whatever was queued there.  A paused animation (bit 2 of the entity's halfword
 * at +4) is resumed first: its held handle (+0x10) is unhooked (02014dc4), the saved track
 * (+0xce), speed (+0xdc = 1.0) and handle (+0xd8) restored and bit 2 dropped.  A motion name
 * ending in ".p2" opens the actor's motion text (+0x1a24, 02024ee8 heap 0xd) when not yet
 * open.  The track's queue head (+0x538) takes the frame, blend and name and the track starts
 * (Ov023_ActorStartMotion 02087298); the rest of that track's queue is emptied (frames -1).
 * With no track holding a motion afterwards flag bit 9 (+0x1a28) is dropped, and on track 0
 * with bit 7 the model is reset (02089174). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;
typedef unsigned int   u32;

typedef struct Ov023Anim {  /* at +4 of the entity */
    u16  wFlags;              /* 0x00 */
    u16  wTrack;              /* 0x02 */
    u8   pad_04[8];
    int  nHandle;             /* 0x0c */
    u8   pad_10[0x10];
    u32  nControl;            /* 0x20 */
    u8   pad_24[0xca - 0x24];
    s16  nSavedTrack;         /* 0xca */
    u8   pad_cc[8];
    int  nSavedHandle;        /* 0xd4 */
    int  nSpeed;              /* 0xd8 */
} Ov023Anim;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    Ov023Anim anim;           /* 0x04 */
} Ov023Entity;

typedef struct Ov023Motion {
    int  nEndFrame;           /* 0x00 */
    s16  nFrame;              /* 0x04 */
    u8   pad_06[2];
    int  nBlend;              /* 0x08 */
    char szName[0x20];        /* 0x0c */
} Ov023Motion;                /* 0x2c */

typedef struct Ov023Actor {
    u8   pad_0000[0x538];
    Ov023Motion aMotion[5][5]; /* 0x0538: [depth][track] */
    u8   pad_0984[0x15e0 - 0x984];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a24 - 0x15e4];
    void *pMotionText;        /* 0x1a24 */
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void  func_02014dc4(u32 *pAnimControl, int nHandle);        /* Anim_Unhook */
extern void  func_0201f924(char *pszDst, const char *pszSrc);       /* STD_CopyString */
extern int   strlen(const char *pszString);
extern int   func_0201fabc(const char *pA, const char *pB);         /* STD_CompareString */
extern void *func_02024ee8(const char *pszName, int nHeap);         /* open a text container */
extern void  func_ov023_02087298(Ov023Actor *pActor, int nTrack);  /* Ov023_ActorStartMotion */
extern void  func_ov023_02089174(Ov023Actor *pActor);               /* Ov023_ResetActorModel */
extern char  data_ov023_0208a730[];                                 /* ".p2" */

void func_ov023_02089390(Ov023Actor *pActor, char *pszMotion, int nFrame, int nTrack, int nBlend)
{
    char szName[0x20];
    Ov023Anim *pAnim;
    int bAny;
    int i;
    Ov023Motion *pMotion;

    pAnim = &pActor->pEntity->anim;
    bAny = 0;
    if (pAnim->wFlags & 4) {
        if (pAnim->nHandle != 0) {
            func_02014dc4(&pAnim->nControl, pAnim->nHandle);
        }
        pAnim->wTrack = pAnim->nSavedTrack;
        pAnim->nSpeed = 0x1000;
        pAnim->nSavedTrack = -1;
        pAnim->nHandle = pAnim->nSavedHandle;
        pAnim->nSavedHandle = 0;
        pAnim->wFlags &= ~4;
    }
    if (pszMotion[0] != 0) {
        func_0201f924(szName, pszMotion);
        if (func_0201fabc(szName + (strlen(szName) - 3), data_ov023_0208a730) == 0 && pActor->pMotionText == 0) {
            pActor->pMotionText = func_02024ee8(szName, 0xd);
        }
    } else {
        szName[0] = 0;
    }
    pMotion = &pActor->aMotion[0][nTrack];
    pMotion->nFrame = nFrame;
    pMotion->nBlend = nBlend;
    func_0201f924(pMotion->szName, szName);
    func_ov023_02087298(pActor, nTrack);
    for (i = 0; i < 5; i++) {
        pActor->aMotion[i][nTrack].nFrame = -1;
    }
    for (i = 0; i < 5; i++) {
        if (pActor->aMotion[0][i].nFrame != -1) {
            bAny = 1;
        }
    }
    if (!bAny) {
        pActor->nFlags &= ~0x200;
    }
    if ((pActor->nFlags & 0x80) && nTrack == 0) {
        func_ov023_02089174(pActor);
    }
}
