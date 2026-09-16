/* func_ov023_02088010 -- Ov023_ActorPopEffect: take the next queued effect (the five 0xc-byte
 * entries at +0x45c: period, effect, mode) as the actor's current one (+4 period, +8 effect,
 * +0xc mode), restarting the timer (+0x454) and clearing the head's mode.  Mode 2 binds the
 * effect as track 0 of the actor's own animation (+0x328, blend table +0x408; 0202accc) and
 * rewinds it to frame 1.0 (01fff774); mode 1 takes half the entity animation's length in
 * frames (0202aef8) as the period.  The queue then moves up one entry until an empty one. */
typedef unsigned char  u8;
typedef signed short   s16;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u8   anim[0x20];          /* 0x04 */
} Ov023Entity;

typedef struct Ov023EffectEntry {
    int  nPeriod;             /* 0x00 */
    int  nEffect;             /* 0x04 */
    int  nMode;               /* 0x08 */
} Ov023EffectEntry;           /* 0x0c */

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    int  nPeriod;             /* 0x0004 */
    int  nEffect;             /* 0x0008 */
    int  nEffectMode;         /* 0x000c */
    u8   pad_0010[0x328 - 0x10];
    u8   anim[0x408 - 0x328]; /* 0x0328 */
    u8   blend[0x454 - 0x408]; /* 0x0408 */
    int  nTimer;              /* 0x0454 */
    int  nField458;           /* 0x0458 */
    Ov023EffectEntry aEffect[5]; /* 0x045c */
    u8   pad_0498[0x15e0 - 0x498];
    Ov023Entity *pEntity;     /* 0x15e0 */
} Ov023Actor;

extern void func_0202accc(void *pAnim, int nTrack, void *pSet, s16 nFrame); /* Anim_PlayTrack */
extern void func_01fff774(void *pAnim, int nTrack, int nFrame);     /* Anim_SetFrameWrapped */
extern int  func_0202aef8(void *pAnim, int nTrack);                 /* Anim_GetLengthQ12 */

void func_ov023_02088010(Ov023Actor *pActor)
{
    int i;

    pActor->nEffect = pActor->aEffect[0].nEffect;
    pActor->nEffectMode = pActor->aEffect[0].nMode;
    pActor->nTimer = 0;
    pActor->aEffect[0].nMode = 0;
    if (pActor->nEffectMode == 2) {
        func_0202accc(pActor->anim, 0, pActor->blend, pActor->nEffect);
        func_01fff774(pActor->anim, 0, 0x1000);
    } else if (pActor->nEffectMode == 1) {
        pActor->nPeriod = (func_0202aef8(pActor->pEntity->anim, 0) >> 12) / 2;
    }
    for (i = 1; i < 5; i++) {
        if (pActor->aEffect[i].nMode == 0) {
            return;
        }
        pActor->aEffect[i - 1].nPeriod = pActor->aEffect[i].nPeriod;
        pActor->aEffect[i - 1].nEffect = pActor->aEffect[i].nEffect;
        pActor->aEffect[i - 1].nMode = pActor->aEffect[i].nMode;
        pActor->aEffect[i].nMode = 0;
    }
}
