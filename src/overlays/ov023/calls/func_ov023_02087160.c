/* func_ov023_02087160 -- Ov023_ActorFinish: take an actor of the event out of play.  Its model
 * is detached (02088f90) and reset (02089174) and its history cleared (02089240); an actor
 * hanging off a parent (+0) drops the parent's child count (+0x1a3c) and, when that reaches
 * 0 while the parent's entity (+0x1a38) has flag bit 2 (0202c424), clears bits 3 / 4 of the
 * entity's halfword at +4 (0202bfcc) and bit 11 of its own flags (+0x1a28); the parent link
 * is cleared.  The flags end as 0x2000. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
} Ov023Entity;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    u8   pad_0004[0x1a28 - 0x4];
    int  nFlags;              /* 0x1a28 */
    u8   pad_1a2c[0x1a38 - 0x1a2c];
    int  nEntity;             /* 0x1a38 */
    int  nChildren;           /* 0x1a3c */
    u8   pad_1a40[0x1a64 - 0x1a40];
} Ov023Actor;

extern void  func_ov023_02088f90(Ov023Actor *pActor);               /* Ov023_DetachActorModel */
extern void  func_ov023_02089174(Ov023Actor *pActor);               /* Ov023_ResetActorModel */
extern void  func_ov023_02089240(Ov023Actor *pActor);               /* Ov023_ResetActorHistory */
extern int   func_0202c424(u16 nEntity);                            /* Entity_GetFlags */
extern Ov023Entity *func_0202bfcc(u16 nEntity);                     /* Entity_Get */

void func_ov023_02087160(Ov023Actor *pActor)
{
    func_ov023_02088f90(pActor);
    func_ov023_02089174(pActor);
    func_ov023_02089240(pActor);
    if (pActor->pParent != 0) {
        pActor->pParent->nChildren--;
        if (pActor->pParent->nChildren == 0 && (func_0202c424((u16)pActor->pParent->nEntity) & 4)) {
            func_0202bfcc((u16)pActor->pParent->nEntity)->wFlags &= ~0x18;
            pActor->nFlags &= ~0x800;
        }
        pActor->pParent = 0;
    }
    pActor->nFlags = 0x2000;
}
