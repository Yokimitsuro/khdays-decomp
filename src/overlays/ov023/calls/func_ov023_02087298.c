/* func_ov023_02087298 -- Ov023_ActorStartMotion: start track nTrack of an actor's motion set
 * (the 0x2c-byte entries at +0x538: s16 nFrame +4, int nBlend +8, char szName[0x20] +0xc).
 * The pending heading is latched first (02087234).  An entry without a name plays the
 * entity's own animation (+0x15e0; 0202accc, or 0202ad74 with a blend) at its frame.  A named
 * entry first shifts the actor's five animation slots (+0x1a20, 0x24 bytes each) up by one,
 * releasing the last (0202a440) and clearing each moved slot's handle (+0xc); then a name
 * ending in ".p2" is bound from the actor's motion text (+0x1a24, 0202a388 with the packed
 * descriptor), otherwise the name (as is when it ends in ".z", else "mi/mo/<name>.z") is
 * loaded (0202a388) and its frame, when not negative, kept; the track is then played from
 * the slot set.  Track 0 also records the frame (+0x1a40) and name (+0x1a44) on the actor. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;
typedef unsigned int   u32;

typedef struct Ov023Motion {
    int  nField00;            /* 0x00 */
    s16  nFrame;              /* 0x04 */
    u8   pad_06[2];
    int  nBlend;              /* 0x08 */
    char szName[0x20];        /* 0x0c */
} Ov023Motion;                /* 0x2c */

typedef struct Ov023AnimSlot {
    int  aField[3];           /* 0x00 */
    int  nHandle;             /* 0x0c */
    int  aField10[5];         /* 0x10 */
} Ov023AnimSlot;              /* 0x24 */

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u8   anim[0xe4 - 0x4];    /* 0x04 */
    u8   blend[0x100 - 0xe4]; /* 0xe4 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x538];
    Ov023Motion aMotion[64];  /* 0x0538 */
    u8   pad_1038[0x15e0 - 0x1038];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a20 - 0x15e4];
    Ov023AnimSlot *pSlots;    /* 0x1a20 */
    void *pMotionText;        /* 0x1a24 */
    u8   pad_1a28[0x1a40 - 0x1a28];
    int  nFrame;              /* 0x1a40 */
    char szMotion[0x20];      /* 0x1a44 */
} Ov023Actor;                 /* 0x1a64 */

extern void  func_ov023_02087234(Ov023Actor *pActor);               /* Ov023_ActorLatchAngle */
extern void  func_0202accc(void *pAnim, u16 nTrack, void *pSet, s16 nFrame);          /* Anim_PlayTrack */
extern void  func_0202ad74(void *pAnim, u16 nTrack, void *pSet, s16 nFrame, int nBlend); /* Anim_PlayTrackBlend */
extern int   strlen(const char *pszString);
extern void  func_0202a440(Ov023AnimSlot *pSlot);                   /* AnimSlot_Release */
extern int   func_0201fabc(const char *pA, const char *pB);         /* STD_CompareString */
extern void  func_0202a388(Ov023AnimSlot *pSlots, void *pAnim, void *pSource, int nHeap); /* AnimSlot_Load */
extern void  func_0201f924(char *pszDst, const char *pszSrc);       /* STD_CopyString */
extern void  OS_SPrintf(char *pBuffer, const char *pFormat, ...);
extern char  data_ov023_0208a730[];                                 /* ".p2" */
extern char  data_ov023_0208a734[];                                 /* ".z" */
extern char  data_ov023_0208a738[];                                 /* "mi/mo/%s.z" */

void func_ov023_02087298(Ov023Actor *pActor, int nTrack)
{
    char szPath[0x100];
    Ov023Motion *pMotion;
    int nLength;
    int nFrame;
    int i;

    pMotion = &pActor->aMotion[nTrack];
    func_ov023_02087234(pActor);
    if (pMotion->szName[0] == 0) {
        if (pMotion->nBlend == 0) {
            func_0202accc(pActor->pEntity->anim, (u16)nTrack, pActor->pEntity->blend, pMotion->nFrame);
        } else {
            func_0202ad74(pActor->pEntity->anim, (u16)nTrack, pActor->pEntity->blend, pMotion->nFrame, pMotion->nBlend);
        }
    } else {
        nLength = strlen(pMotion->szName);
        nFrame = 0;
        for (i = 4; i >= 0; i--) {
            if (pActor->pSlots[i].nHandle != 0) {
                if (i == 4) {
                    func_0202a440(&pActor->pSlots[i]);
                    pActor->pSlots[i].nHandle = 0;
                } else {
                    pActor->pSlots[i + 1] = pActor->pSlots[i];
                    pActor->pSlots[i].nHandle = 0;
                }
            }
        }
        if (func_0201fabc(pMotion->szName + (nLength - 3), data_ov023_0208a730) == 0) {
            func_0202a388(pActor->pSlots, pActor->pEntity->anim,
                          (void *)(((((u32)pActor->pMotionText + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (pMotion->nFrame & (0xfffffc >> 15))),
                          0xd);
        } else {
            if (func_0201fabc(pMotion->szName + (nLength - 2), data_ov023_0208a734) == 0) {
                func_0201f924(szPath, pMotion->szName);
            } else {
                OS_SPrintf(szPath, data_ov023_0208a738, pMotion->szName);
            }
            func_0202a388(pActor->pSlots, pActor->pEntity->anim, szPath, 0xd);
            if (pMotion->nFrame >= 0) {
                nFrame = pMotion->nFrame;
            }
        }
        if (pMotion->nBlend == 0) {
            func_0202accc(pActor->pEntity->anim, (u16)nTrack, pActor->pSlots, nFrame);
        } else {
            func_0202ad74(pActor->pEntity->anim, (u16)nTrack, pActor->pSlots, nFrame, pMotion->nBlend);
        }
    }
    if (nTrack == 0) {
        pActor->nFrame = pMotion->nFrame;
        func_0201f924(pActor->szMotion, pMotion->szName);
    }
}
