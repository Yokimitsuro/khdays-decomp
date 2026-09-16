/* func_ov023_02083508 -- Ov023_ReleaseScreenActors: walk the 0x40 actors of the event scene
 * (the 0x1a64-byte entries the pointer at +0x1daf0 points to) and, for each one whose panel
 * currently tracks the departed peer (+0x87590; Ov023_ActorOnScreen 02088ec0), finish it
 * (0208895c) unless the scene's dialog state (+0x875e4) is 2 or 3 (an ov002 dialog up), and release its sprite id
 * (0202beb8 with the actor index) when its state word (02088eb4) has bit 5 or bit 10 set. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov023Actor {
    u8   pad_0000[0x1a64];
} Ov023Actor;

typedef struct Ov023Scene {
    u8   pad_00000[0x1daf0];
    Ov023Actor *pActors;      /* 0x1daf0: the 0x40 actors at +0x1dc54 */
    u8   pad_1daf4[0x87590 - 0x1daf4];
    int  nActiveScreen;           /* 0x87590 */
    u8   pad_87594[0x875e4 - 0x87594];
    int  nDialogState;         /* 0x875e4 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern int  func_ov023_02088ec0(Ov023Actor *pActor, int nPeer);     /* Ov023_ActorOnScreen */
extern void func_ov023_0208895c(Ov023Actor *pActor);                /* finish the actor */
extern int  func_ov023_02088eb4(Ov023Actor *pActor);                /* the actor's state word */
extern void func_0202beb8(u16 nId, int bOn);                        /* release a sprite id */
extern Ov023SceneRoot data_ov023_0208a784;

void func_ov023_02083508(void)
{
    int i;
    int nOffset;

    i = 0;
    nOffset = 0;
    for (; i < 0x40; i++) {
        if (func_ov023_02088ec0((Ov023Actor *)((u8 *)data_ov023_0208a784.pScene->pActors + nOffset), data_ov023_0208a784.pScene->nActiveScreen)) {
            if (data_ov023_0208a784.pScene->nDialogState != 3 && data_ov023_0208a784.pScene->nDialogState != 2) {
                func_ov023_0208895c((Ov023Actor *)((u8 *)data_ov023_0208a784.pScene->pActors + nOffset));
            }
            if (func_ov023_02088eb4((Ov023Actor *)((u8 *)data_ov023_0208a784.pScene->pActors + nOffset)) & 0x420) {
                func_0202beb8(i, 0);
            }
        }
        nOffset += sizeof(Ov023Actor);
    }
}
