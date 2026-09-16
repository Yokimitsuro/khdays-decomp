/* func_ov023_02087564 -- Ov023_ActorFindRotTween: find the rotation tween slot of a joint among the actor's seven
 * rotation tweens (+0x984, 0x28 bytes each, joint at +0x18).  Returns the index of the tween
 * already on the joint, else the first free tween (joint -1), else -1. */
typedef unsigned char  u8;

typedef struct Ov023RotTween {
    u8   pad_00[0x18];
    int  nJoint;              /* 0x18 */
    u8   pad_1c[0x28 - 0x1c];
} Ov023RotTween;               /* 0x28 */

typedef struct Ov023Actor {
    u8   pad_0000[0x984];
    Ov023RotTween aRotTween[7]; /* 0x0984 */
} Ov023Actor;

int func_ov023_02087564(Ov023Actor *pActor, int nJoint)
{
    int i;
    int nResult;
    Ov023RotTween *pTween;

    pTween = pActor->aRotTween;
    nResult = -1;
    for (i = 0; i < 7; i++) {
        if (nJoint == pTween->nJoint) {
            nResult = i;
            break;
        }
        if (pTween->nJoint == -1 && nResult == -1) {
            nResult = i;
        }
        pTween++;
    }
    return nResult;
}
