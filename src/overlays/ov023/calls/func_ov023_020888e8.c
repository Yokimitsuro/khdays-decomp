/* func_ov023_020888e8 -- Ov023_ActorRelease: free what an actor of the event owns.  Its motion
 * text (+0x1a24) is closed (02024fd4); an actor still in play (flags +0x1a28 not 0) is
 * finished (Ov023_ActorFinish 02087160) and its animation slots (+0x1a20, five of 0x24 bytes)
 * released one by one where loaded (handle +0xc, 0202a440) and freed
 * (NNSi_FndFreeFromDefaultHeap); the flags end as 0. */
typedef unsigned char  u8;

typedef struct Ov023AnimSlot {
    int  aField[3];           /* 0x00 */
    int  nHandle;             /* 0x0c */
    int  aField10[5];         /* 0x10 */
} Ov023AnimSlot;              /* 0x24 */

typedef struct Ov023Actor {
    u8   pad_0000[0x1a20];
    Ov023AnimSlot *pSlots;    /* 0x1a20 */
    void *pMotionText;        /* 0x1a24 */
    int  nFlags;              /* 0x1a28 */
} Ov023Actor;

extern void func_02024fd4(void *pContainer);                        /* close a text container */
extern void func_ov023_02087160(Ov023Actor *pActor);                /* Ov023_ActorFinish */
extern void func_0202a440(Ov023AnimSlot *pSlot);                    /* AnimSlot_Release */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);

void func_ov023_020888e8(Ov023Actor *pActor)
{
    int i;

    if (pActor->pMotionText != 0) {
        func_02024fd4(pActor->pMotionText);
        pActor->pMotionText = 0;
    }
    if (pActor->nFlags != 0) {
        func_ov023_02087160(pActor);
        if (pActor->pSlots != 0) {
            for (i = 0; i < 5; i++) {
                if (pActor->pSlots[i].nHandle != 0) {
                    func_0202a440(&pActor->pSlots[i]);
                }
            }
            NNSi_FndFreeFromDefaultHeap(pActor->pSlots);
            pActor->pSlots = 0;
        }
        pActor->nFlags = 0;
    }
}
