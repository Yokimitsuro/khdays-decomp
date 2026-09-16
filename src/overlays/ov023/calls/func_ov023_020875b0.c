/* func_ov023_020875b0 -- Ov023_ActorSampleTrack: advance the actor's entity animation once with
 * bits 0 and 1 of its control word (+0x24 of the entity at +0x15e0) set (020279e0), drop bit 1
 * again and return the position of the actor's current track (+0x15b0 into the 0x58-byte
 * track entries at +0xac4, position at +0x24). */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct VecFx32 {
    int  x;                   /* 0x00 */
    int  y;                   /* 0x04 */
    int  z;                   /* 0x08 */
} VecFx32;

typedef struct Ov023Entity {
    u8   pad_00[0x24];
    u32  nAnimControl;        /* 0x24 */
} Ov023Entity;

typedef struct Ov023Track {
    u8   pad_00[0x24];
    VecFx32 vPos;             /* 0x24 */
    u8   pad_30[0x58 - 0x30];
} Ov023Track;                 /* 0x58 */

typedef struct Ov023Actor {
    u8   pad_0000[0xac4];
    Ov023Track aTrack[1];     /* 0x0ac4 */
    u8   pad_0b1c[0x15b0 - 0xb1c];
    int  nTrack;              /* 0x15b0 */
    u8   pad_15b4[0x15e0 - 0x15b4];
    Ov023Entity *pEntity;     /* 0x15e0 */
} Ov023Actor;

extern void func_020279e0(u32 *pAnimControl);                       /* Anim_Advance */

void func_ov023_020875b0(Ov023Actor *pActor, VecFx32 *pOut)
{
    pActor->pEntity->nAnimControl |= 1;
    pActor->pEntity->nAnimControl |= 2;
    func_020279e0(&pActor->pEntity->nAnimControl);
    pActor->pEntity->nAnimControl &= ~2;
    *pOut = pActor->aTrack[pActor->nTrack].vPos;
}
