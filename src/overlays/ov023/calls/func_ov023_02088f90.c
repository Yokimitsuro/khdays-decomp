/* func_ov023_02088f90 -- Ov023_DetachActorModel: take a tracking actor (flag bit 6, +0x1a28)
 * off its motion track.  The pending heading is latched first (Ov023_ActorLatchAngle
 * 02087234); then bit 0 of the entity's animation control (+0x24 of +0x15e0) is cleared unless
 * a track frame is pending (+0x38 of it), the track pointer (+0x34) cleared, bit 6 dropped, the
 * track (+0x15b0) set to -1, the turn state (+0x15b4), the last track sample (+0x159c) and the
 * angle offset (+0x15a8) cleared. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023AnimCtl {
    u32  nControl;            /* 0x00 */
    u8   pad_04[0x34 - 0x04];
    void *pTracks;            /* 0x34 */
    int  nTrackPending;       /* 0x38 */
} Ov023AnimCtl;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x24 - 0x06];
    Ov023AnimCtl anim;        /* 0x24 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x159c];
    VecFx32 vTrackPos;        /* 0x159c */
    int  nAngleOffset;        /* 0x15a8 */
    int  nHeightOffset;       /* 0x15ac */
    int  nTrack;              /* 0x15b0 */
    int  nTurnState;          /* 0x15b4 */
    u8   pad_15b8[0x15e0 - 0x15b8];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a28 - 0x15e4];
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void func_ov023_02087234(Ov023Actor *pActor);               /* Ov023_ActorLatchAngle */

void func_ov023_02088f90(Ov023Actor *pActor)
{
    Ov023AnimCtl *pAnim;

    if (pActor->nFlags & 0x40) {
        func_ov023_02087234(pActor);
        pAnim = &pActor->pEntity->anim;
        if (pAnim->nTrackPending == 0) {
            pAnim->nControl &= ~1;
        }
        pAnim->pTracks = 0;
        pActor->nFlags &= ~0x40;
        pActor->nTrack = -1;
        pActor->nTurnState = 0;
        pActor->vTrackPos.x = pActor->vTrackPos.y = pActor->vTrackPos.z = 0;
        pActor->nAngleOffset = 0;
    }
}
