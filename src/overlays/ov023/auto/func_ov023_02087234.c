/* func_ov023_02087234 -- Ov023_ActorLatchAngle: in turn state 2 (+0x15b4) take the actor's
 * heading from its entity (+0x15e0; +0x80) plus the actor's angle offset (+0x15a8), as a u16,
 * as both the current and target angle (+0x1a30 / +0x1a34), push it back onto the entity
 * (+0x80, flag bit 5 of +4) unless the entity's bit 5 at +0 is set, and leave state 0. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x80 - 0x06];
    u16  nAngle;              /* 0x80 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x15a8];
    int  nAngleOffset;        /* 0x15a8 */
    u8   pad_15ac[8];
    int  nTurnState;          /* 0x15b4 */
    u8   pad_15b8[0x15e0 - 0x15b8];
    Ov023Entity *pEntity;     /* 0x15e0 */
    u8   pad_15e4[0x1a30 - 0x15e4];
    int  nAngle;              /* 0x1a30 */
    int  nAngleTarget;        /* 0x1a34 */
    u8   pad_1a38[0x1a64 - 0x1a38];
} Ov023Actor;

/* Give an entity a heading unless it is locked (bit 5 of its flags). */
static inline void Ov023_EntitySetAngle(Ov023Entity *pEntity, int nAngle)
{
    if (!(pEntity->nFlags & 0x20)) {
        pEntity->nAngle = nAngle;
        pEntity->wFlags |= 0x20;
    }
}

void func_ov023_02087234(Ov023Actor *pActor)
{
    if (pActor->nTurnState != 2) {
        return;
    }
    pActor->nAngle = (u16)(pActor->nAngleOffset + pActor->pEntity->nAngle);
    pActor->nAngleTarget = pActor->nAngle;
    Ov023_EntitySetAngle(pActor->pEntity, pActor->nAngle);
    pActor->nTurnState = 0;
}
