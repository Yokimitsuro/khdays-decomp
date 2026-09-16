/* func_ov023_02088d18 -- Ov023_ActorHookJoints: make an actor the one whose joint rotation
 * tweens (+0x984, seven of 0x28 bytes) the joint hook draws: their addresses fill
 * data_ov023_0208a7a0, the hook Ov023_DrawJointRotations (020885fc) is installed on the
 * entity's animation (+0x15e0; +0x24; 02014e18 with 0 / 6 / 3) and the hook value at +0x2c of
 * data_ov023_0208a790 records whether the entity has bit 4 of its halfword at +4. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

typedef struct Ov023RotTween {
    u8   pad_00[0x28];
} Ov023RotTween;              /* 0x28 */

typedef struct Ov023Entity {
    int  nFlags;              /* 0x00 */
    u16  wFlags;              /* 0x04 */
    u8   pad_06[0x24 - 0x06];
    u32  nAnimControl;        /* 0x24 */
} Ov023Entity;

typedef struct Ov023Actor {
    u8   pad_0000[0x984];
    Ov023RotTween aRotTween[7]; /* 0x0984 */
    u8   pad_0a9c[0x15e0 - 0xa9c];
    Ov023Entity *pEntity;     /* 0x15e0 */
} Ov023Actor;

typedef struct Ov023JointHook {
    u8   pad_00[0x2c];
    int  nValue;              /* 0x2c */
} Ov023JointHook;

extern void func_02014e18(u32 *pAnimControl, void *pfnHook, int nA, int nCommand, int nB); /* Anim_SetJointHook */
extern void func_ov023_020885fc(void *pNode);                       /* Ov023_DrawJointRotations */
extern Ov023RotTween *data_ov023_0208a7a0[7];                       /* the joint rotation tweens */
extern Ov023JointHook data_ov023_0208a790;

void func_ov023_02088d18(Ov023Actor *pActor)
{
    int i;

    for (i = 0; i < 7; i++) {
        data_ov023_0208a7a0[i] = &pActor->aRotTween[i];
    }
    func_02014e18(&pActor->pEntity->nAnimControl, func_ov023_020885fc, 0, 6, 3);
    data_ov023_0208a790.nValue = (pActor->pEntity->wFlags & 0x10) != 0;
}
