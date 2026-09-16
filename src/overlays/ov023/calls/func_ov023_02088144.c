/* func_ov023_02088144 -- Ov023_ActorUpdateMotions: run an actor's five motion tracks for one
 * frame.  The entity's finished-track mask (0202a928 with the entity speed 0202c6a8) is taken;
 * for each track whose queue head (+0x538, 0x2c bytes per track) holds a motion (frame not -1
 * or a name), the track fires when its mask bit is set and the entity is not paused (bit 2 of
 * +4), or, for track 0 only, when the animation's frame (0202aee0) has reached the head's end
 * frame.  A firing track flushes the queued sounds (020880e0); a head frame of -2 ends the
 * actor (every track rewound, the entity released 0202bc0c, Ov023_ActorFinish 02087160),
 * otherwise the next queued motion starts (Ov023_ActorPopMotion 02087f68) and, on track 0,
 * flag bit 6 restarts the actor's own animation (02087210, frame 1.0), the new end frame
 * (0202aef8 - 1.0) is stored, and a queued effect is popped (02088010) or, with flag bit 7,
 * the model reset (02089174).  With every queue empty afterwards flag bit 9 is dropped and,
 * with bit 6, the model detached (02088f90). */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04: the animation starts here */
    u8   pad_06[0x20 - 0x06];
} Ov023Entity;

typedef struct Ov023Motion {
    int  nEndFrame;           /* 0x00 */
    s16  nFrame;              /* 0x04 */
    u8   pad_06[2];
    int  nBlend;              /* 0x08 */
    char szName[0x20];        /* 0x0c */
} Ov023Motion;                /* 0x2c */

typedef struct Ov023EffectEntry {
    int  nPeriod;             /* 0x00 */
    int  nEffect;             /* 0x04 */
    int  nMode;               /* 0x08 */
} Ov023EffectEntry;           /* 0x0c */

typedef struct Ov023Actor {
    u8   pad_0000[0x45c];
    Ov023EffectEntry aEffect[5]; /* 0x045c */
    u8   pad_0498[0x538 - 0x498];
    Ov023Motion aMotion[5][5]; /* 0x0538: [depth][track] */
    u8   pad_0984[0x15e0 - 0x984];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a28 - 0x15e4];
    int  nFlags;              /* 0x1a28 */
    u8   pad_1a2c[0x1a38 - 0x1a2c];
    int  nEntity;             /* 0x1a38 */
} Ov023Actor;

extern int  func_0202c6a8(u16 nEntity);                             /* Entity_GetSpeed */
extern int  func_0202a928(void *pAnim, int nSpeed);                 /* Anim_GetFinishedMask */
extern int  func_0202aee0(void *pAnim, u16 nTrack);                 /* Anim_GetFrame */
extern void func_ov023_020880e0(Ov023Actor *pActor);                /* Ov023_ActorFlushSounds */
extern void func_01fff774(void *pAnim, u16 nTrack, int nFrame);     /* Anim_SetFrameWrapped */
extern void SNDi_ProcessEntryAlt(u16 nEntity);                      /* Entity_Release (0202bc0c) */
extern void func_ov023_02087160(Ov023Actor *pActor);                /* Ov023_ActorFinish */
extern void func_ov023_02087f68(Ov023Actor *pActor, int nTrack);    /* Ov023_ActorPopMotion */
extern void func_ov023_02087210(Ov023Actor *pActor);                /* Ov023_ActorRestartAnim */
extern int  func_0202aef8(void *pAnim, u16 nTrack);                 /* Anim_GetLengthQ12 */
extern void func_ov023_02088010(Ov023Actor *pActor);                /* Ov023_ActorPopEffect */
extern void func_ov023_02089174(Ov023Actor *pActor);                /* Ov023_ResetActorModel */
extern void func_ov023_02088f90(Ov023Actor *pActor);                /* Ov023_DetachActorModel */

void func_ov023_02088144(Ov023Actor *pActor)
{
    int bAny;
    int nEntity;
    int nMask;
    Ov023Entity *pEntity;
    int bFire;
    int i;
    int j;
    Ov023Motion *pMotion;

    nEntity = pActor->nEntity;
    bAny = 0;
    pEntity = pActor->pEntity;
    bFire = bAny;
    nMask = func_0202a928(&pEntity->wFlags, func_0202c6a8((u16)nEntity));
    for (i = 0; i < 5; i++) {
        pMotion = &pActor->aMotion[0][i];
        if (pMotion->nFrame == -1 && pMotion->szName[0] == 0) {
            continue;
        }
        if (nMask & (1 << i)) {
            if (!(pEntity->wFlags & 4)) {
                bFire = 1;
            }
        } else if (i == 0) {
            if (func_0202aee0(&pEntity->wFlags, (u16)i) >= pMotion->nEndFrame) {
                bFire = 1;
            }
        }
        if (bFire) {
            func_ov023_020880e0(pActor);
            if (pMotion->nFrame == -2) {
                if (pActor->pEntity != 0) {
                    for (j = 0; j < 5; j++) {
                        func_01fff774(&pEntity->wFlags, (u16)j, 0);
                    }
                }
                SNDi_ProcessEntryAlt((u16)pActor->nEntity);
                func_ov023_02087160(pActor);
                return;
            }
            func_ov023_02087f68(pActor, i);
            if (i == 0) {
                if (pActor->nFlags & 0x40) {
                    func_ov023_02087210(pActor);
                    func_01fff774(&pEntity->wFlags, 0, 0x1000);
                }
                pActor->aMotion[0][i].nEndFrame = func_0202aef8(&pEntity->wFlags, (u16)i) - 0x1000;
                if (pActor->aEffect[0].nMode != 0) {
                    func_ov023_02088010(pActor);
                } else if (pActor->nFlags & 0x80) {
                    func_ov023_02089174(pActor);
                }
            }
        }
        if (!(pMotion->nFrame == -1 && pMotion->szName[0] == 0)) {
            bAny = 1;
        }
    }
    if (bAny) {
        return;
    }
    pActor->nFlags &= ~0x200;
    if (pActor->nFlags & 0x40) {
        func_ov023_02088f90(pActor);
    }
}
