/* func_ov023_02089174 -- Ov023_ResetActorModel: drop an actor's model-side state (flag bit 7,
 * +0x1a28).  With an effect animation loaded (bit 8) its motion state (+4) is unhooked -- bit 0
 * of the control word (+0x344) cleared unless the word at +0x37c is set, the owner pointer
 * (+0x378) cleared, the animation released (0202a7dc on +0x324) -- and bit 8 dropped; then
 * bit 7 is dropped and the five queued effects (+0x45c) wiped. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov023MotionState {  /* at +4 of the actor */
    u8   pad_000[0x324];
    u8   anim[0x20];          /* 0x324 */
    u32  nAnimControl;        /* 0x344 */
    u8   pad_348[0x378 - 0x348];
    int *pOwner;              /* 0x378 */
    int  nField37c;           /* 0x37c */
} Ov023MotionState;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    Ov023MotionState motion;  /* 0x0004 */
    u8   pad_0384[0x45c - 0x384];
    u8   aEffect[0x3c];       /* 0x045c */
    u8   pad_0498[0x1a28 - 0x498];
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void func_0202a7dc(void *pAnim);                             /* Anim_Release */
extern void MI_CpuFill8(void *pDst, u32 nValue, u32 nSize);

void func_ov023_02089174(Ov023Actor *pActor)
{
    int nFlags;
    Ov023MotionState *pState;

    pState = &pActor->motion;
    nFlags = pActor->nFlags;
    if (nFlags & 0x80) {
        if (nFlags & 0x100) {
            if (pState->nField37c == 0) {
                pState->nAnimControl &= ~1;
            }
            pState->pOwner = 0;
            func_0202a7dc(pState->anim);
            pActor->nFlags &= ~0x100;
        }
        pActor->nFlags &= ~0x80;
        MI_CpuFill8(pActor->aEffect, 0, 0x3c);
    }
}
