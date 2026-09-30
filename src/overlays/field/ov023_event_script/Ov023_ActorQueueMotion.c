/* Ov023_ActorQueueMotion -- Ov023_ActorQueueMotion: queue a motion on one of an actor's tracks.
 * The first free depth of the track's queue (+0x538, frame -1) takes the frame, the name (a
 * name ending in ".p2" opens the actor's motion text at +0x1a24 when not yet open, 02024ee8
 * heap 0xd) and the blend.  On track 0 its end frame is chosen from the entity's animation
 * (+0x15e0): with the halfway flag, half the length (0202aef8) unless the current frame
 * (0202aee0) is already past it, then the full length; without it the full length less the
 * entity speed (0202c6a8 on +0x1a38) unless the actor tracks (flag bit 6, +0x1a28).  The
 * depth's two sound requests (+0x498) are cleared.  Flag bit 9 is set either way. */

#include "nitro/types.h"

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04: the animation starts here */
} Ov023Entity;

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
    u8   pad_0984[0x15e0 - 0x984];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a24 - 0x15e4];
    void *pMotionText;        /* 0x1a24 */
    int  nFlags;              /* 0x1a28 */
    u8   pad_1a2c[0x1a38 - 0x1a2c];
    int  nEntity;             /* 0x1a38 */
} Ov023Actor;

extern void  strcpy(char *pszDst, const char *pszSrc);       /* STD_CopyString */
extern int   strlen(const char *pszString);
extern int   strcmp(const char *pA, const char *pB);         /* STD_CompareString */
extern void *Msg_OpenContainerAndReadHeader(const char *pszName, int nHeap);         /* open a text container */
extern int   Anim_GetLengthQ12(void *pAnim, int nTrack);                /* Anim_GetLengthQ12 */
extern int   Anim_GetFrame(void *pAnim, int nTrack);                /* Anim_GetFrame */
extern int   LoadArrayInt244(int nEntity);                            /* Entity_GetSpeed */
extern char  gOv023P2Name_2[];                                 /* ".p2" */

void Ov023_ActorQueueMotion(Ov023Actor *pActor, char *pszMotion, s16 nFrame, int nTrack, int nBlend, int bHalfway)
{
    int i;
    int j;
    Ov023Motion *pMotion;
    int nLength;
    int nCurrent;

    for (i = 0; i < 5; i++) {
        pMotion = &pActor->aMotion[i][nTrack];
        if (pMotion->nFrame != -1) {
            continue;
        }
        pMotion->nFrame = nFrame;
        if (pszMotion == 0 || pszMotion[0] == 0) {
            pMotion->szName[0] = 0;
        } else {
            strcpy(pMotion->szName, pszMotion);
            if (strcmp(pMotion->szName + (strlen(pMotion->szName) - 3), gOv023P2Name_2) == 0
                && pActor->pMotionText == 0) {
                pActor->pMotionText = Msg_OpenContainerAndReadHeader(pszMotion, 0xd);
            }
        }
        pMotion->nBlend = nBlend;
        if (nTrack == 0) {
            nLength = Anim_GetLengthQ12(&pActor->pEntity->wFlags, nTrack & 0xffff);
            nCurrent = Anim_GetFrame(&pActor->pEntity->wFlags, (u16)((u16)nTrack));
            if (bHalfway != 0) {
                if (nCurrent < nLength / 2) {
                    pMotion->nEndFrame = nLength / 2;
                } else {
                    pMotion->nEndFrame = nLength;
                }
            } else {
                pMotion->nEndFrame = nLength;
                if (!(pActor->nFlags & 0x40)) {
                    pMotion->nEndFrame -= LoadArrayInt244((u16)((u16)pActor->nEntity));
                }
            }
        }
        for (j = 0; j < 2; j++) {
            pActor->aSound[i][j].nKind = 0;
        }
        break;
    }
    pActor->nFlags |= 0x200;
}
