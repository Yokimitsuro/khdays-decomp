/* func_ov023_02089000 -- Ov023_ActorLoadEffectAnim: give an actor its own effect animation.
 * Flag bit 8 (+0x1a28) is set, the animation loaded from the resource into the motion state
 * (+4; its animation at +0x324, 0202a6a0 with 0 / heap 0xd), the nine effect tracks looked up
 * by name (data_ov023_0208a70c: ro_walk00, ro_walk01, ro_dash00, ro_dash01, 13_walk00,
 * 13_walk01, 13_dash00, 13_dash01, 13_hakusyu00; 02087510 into +0x42c), the state's owner
 * pointer (+0x378) aimed at the actor's word at +0x10 and bit 1 of its control word (+0x344)
 * set. */
typedef unsigned char  u8;
typedef unsigned int   u32;

typedef struct Ov023MotionState {  /* at +4 of the actor */
    int  nPeriod;             /* 0x000 */
    int  nEffect;             /* 0x004 */
    int  nEffectMode;         /* 0x008 */
    int  nField00c;           /* 0x00c */
    u8   pad_010[0x324 - 0x10];
    u8   anim[0x20];          /* 0x324 */
    u32  nAnimControl;        /* 0x344 */
    u8   pad_348[0x378 - 0x348];
    int *pOwner;              /* 0x378 */
    u8   pad_37c[0x42c - 0x37c];
    int  aTrackIndex[9];      /* 0x42c */
} Ov023MotionState;

typedef struct Ov023Actor {
    struct Ov023Actor *pParent; /* 0x0000 */
    Ov023MotionState motion;  /* 0x0004 */
    u8   pad_0454[0x1a28 - 0x454];
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void func_0202a6a0(void *pAnim, void *pResource, int nArg, int nHeap); /* Anim_Load */
extern int  func_ov023_02087510(void *pAnim, char *pszTrack);      /* Ov023_FindAnimTrack */
extern char *data_ov023_0208a70c[9];                                /* the effect track names */

void func_ov023_02089000(Ov023Actor *pActor, void *pResource)
{
    Ov023MotionState *pState;
    int i;

    pActor->nFlags |= 0x100;
    pState = &pActor->motion;
    func_0202a6a0(pState->anim, pResource, 0, 0xd);
    for (i = 0; i < 9; i++) {
        pState->aTrackIndex[i] = func_ov023_02087510(pState->anim, data_ov023_0208a70c[i]);
    }
    pState->pOwner = &pState->nField00c;
    pState->nAnimControl |= 2;
}
