/* Ov022_EndAnchoredAction -- close an anchored action: leave the state or
 * turn the actor to its target.
 *
 * The local player raises flag-2 bit 29 and flag-3 bit 29; input bit 6 goes
 * up. Without flag bit 24 the state ends: into state 0 with input bit 2 held,
 * into state 2 otherwise. With it, an actor whose entry is live and whose
 * target reference is valid is turned toward the target (the angle clamped
 * toward it), unless the node is already skipping its animation. When the
 * state did end, flag bits 45, 19 and 7, input bit 6 and flag-3 bit 29 are
 * all dropped.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

/* Ov022ActorNode */
struct ActorNode {
    u32 nFlags;                  /* 0x00 */
    u16 nAnimFlags;              /* 0x04 */
    u8 pad06[0x7a];
    u16 nAngle;                  /* 0x80 */
};

/* Ov022Actor */
struct Actor {
    u64 nFlags;                  /* 0x0000 */
    u8 pad0008[1];
    u8 nId;                      /* 0x0009 */
    u8 pad000a[0x16];
    struct ActorNode *pNode;     /* 0x0020 */
    u32 nInputMask;              /* 0x0024 */
    u8 pad0028[0x43c];
    u64 nFlags2;                 /* 0x0464 */
    u64 nFlags3;                 /* 0x046c */
    u8 pad0474[0x18];
    VecFx32 vecAim;              /* 0x048c */
};

#define FLAG_BIT7 (1ULL << 7)
#define FLAG_BIT19 (1ULL << 19)
#define FLAG_BIT24 (1ULL << 24)
#define FLAG_BIT45 (1ULL << 45)
#define FLAG2_BIT29 (1ULL << 29)
#define FLAG3_BIT29 (1ULL << 29)
#define INPUT_BIT2 0x4
#define INPUT_BIT6 0x40
#define NODE_NO_ANIM 0x20
#define ANIM_HOLD 0x20
#define ANGLE_BIAS 0x8000
#define STATE_IDLE 0
#define STATE_END 2

extern int func_02030788(void);
extern int func_ov022_020a35f4(struct Actor *pActor, int nState);   /* Ov022_ActorSetState */
extern int func_ov002_020767d4(u16 nIndex);
extern int func_ov022_020ad114(struct Actor *pActor);              /* Ov022_ValidateTargetRef */
extern VecFx32 *func_ov022_020ad0c0(struct Actor *pActor);
extern void VEC_Subtract(VecFx32 *pA, VecFx32 *pB, VecFx32 *pOut);
extern int VEC_Mag(VecFx32 *pVec);
extern void func_01ff8d18(VecFx32 *pSrc, VecFx32 *pDst);           /* VEC_Normalize */
extern int FX_Atan2(int x, int z);
extern int func_ov022_020ad4e8(struct Actor *pActor, u32 nAngle);  /* Ov022_ClampAngleTowardTarget */

int func_ov022_020ab57c(struct Actor *pActor)
{
    VecFx32 vecDir;
    int nRet;
    int nAngle;
    struct ActorNode *pNode;

    nRet = 0;
    if (func_02030788() == 0) {
        pActor->nFlags2 |= FLAG2_BIT29;
    }
    if (func_02030788() == 0) {
        pActor->nFlags3 |= FLAG3_BIT29;
    }
    pActor->nInputMask |= INPUT_BIT6;
    if ((pActor->nFlags & FLAG_BIT24) == 0) {
        if ((pActor->nInputMask & INPUT_BIT2) != 0) {
            nRet = func_ov022_020a35f4(pActor, STATE_IDLE);
        } else {
            nRet = func_ov022_020a35f4(pActor, STATE_END);
        }
    } else {
        if (func_ov002_020767d4(pActor->nId) != 0 && func_ov022_020ad114(pActor) != 0) {
            VEC_Subtract(func_ov022_020ad0c0(pActor), &pActor->vecAim, &vecDir);
            if (VEC_Mag(&vecDir) != 0) {
                func_01ff8d18(&vecDir, &vecDir);
            }
            nAngle = func_ov022_020ad4e8(pActor, (u16)FX_Atan2(-vecDir.x, -vecDir.z));
            pNode = pActor->pNode;
            if ((pNode->nFlags & NODE_NO_ANIM) == 0) {
                pNode->nAngle = nAngle + ANGLE_BIAS;
                pNode->nAnimFlags |= ANIM_HOLD;
            }
        }
    }
    if (nRet != 0) {
        pActor->nFlags &= ~FLAG_BIT45;
        pActor->nFlags &= ~FLAG_BIT19;
        pActor->nFlags &= ~FLAG_BIT7;
        pActor->nInputMask &= ~INPUT_BIT6;
        pActor->nFlags3 &= ~FLAG3_BIT29;
    }
    return nRet;
}
