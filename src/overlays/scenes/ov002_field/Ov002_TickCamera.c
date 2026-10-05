
#include "nitro/fx_types.h"

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int QueryActiveStateOrDelegate(void);
extern void *GetEntryField20ByIndex(int nPlayer);
extern void *Obj_GetCurrent(void);   /* the active actor */
extern int FX_Div(int a, int b);
extern short FX_Atan2Idx(int x, int y);
/* Cosine to angle: a binary search over the shared sin/cos table. The other
 * three registers Ghidra shows at the call site are the callee's own locals. */
extern unsigned short FX_AcosIdx(int nCos);
extern void func_0201653c(int *pObj, int *pOutA, int *pOutB);
extern void func_020166c4(int a, int b, int *pOut, int *pWork);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *v, VecFx32 *out);   /* normalise */

extern void *func_ov022_020881f8(int player);
extern int func_ov022_02083f5c(void);
extern int func_ov022_020881d8(void);
extern int func_ov022_02088338(void);
extern int Ov022_IsBit2SetVia0x20(int nHandle);
extern int *func_ov022_020865b4(void);
extern int func_ov022_020886d0(int nPlayer);

extern void Ov002_ClearPendingOnBoot(void);
extern void Ov002_Camera_UpdateFollow(void);
extern int Ov002_IsPointOnScreen(unsigned int *pOutBits, int *pObj, int nMaskA,
                               int nMaskB);
extern int Ov002_IsAngleBeyondLimit(int nAngleA, int nAngleB);
extern int Ov002_TurnAngleToward(int nAngleA, int nAngleB);
extern void Ov002_PlaceCameraForFrame(VecFx32 *pOutFocus, VecFx32 *pOutCamera,
                                int *pOutDist, VecFx32 *pAnchor, int nAngle,
                                int nDist, int nPrevDist);
extern void Ov002_TickCameraTransition(void *pActor);
extern int Ov002_GetCameraDistance(int nSlot);
extern int Ov002_Camera_GetPresetHeight(int nSlot);
extern int Ov002_UpdateCameraDistance(int nSlot);

extern unsigned char data_0204be04;
extern unsigned short gPadPressed;
extern VecFx32 data_020475ac;

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

/* Camera tick: one frame of camera state, and the next handler to run.
 *
 * Returns the handler at Ov002_Camera_UpdateFollow, or null to stay put. Nothing runs
 * at all while the camera's stage id at +0xe0 disagrees with the global one,
 * while flag bit 4 is set, or while the session says so.
 *
 * Then one of three arms. The reset arm runs when the session has no valid
 * target or the flags carry an inhibit bit: it clears bit 0x20, reloads the
 * pitch and its limit from the distance table, and, when the boot gate says so,
 * sets bits 0x2800 and kicks the actor tick. Both working arms end the same
 * way - refresh the distance, place the camera, run the actor tick on the
 * scene.
 *
 * The arm taken when bit 0x40 or 0x80 is set tracks a held point: it nudges the
 * pitch by the stick bits, takes the flat direction from the target to that
 * point, and steers the target yaw toward its angle. The other arm tracks the
 * actor: the same nudge at a gentler rate, an extra approach of the pitch
 * toward the table value, and a yaw derived by projecting two screen points
 * into the world and taking the angle between them.
 *
 * Branch layout follows the ROM: the reset arm is the then arm of the guard
 * chain, and of the two working arms the one gated on bits 0x40 or 0x80 falls
 * through, so it is written first. Three of the helper prototypes matter for
 * the codegen and are NOT what the decompiler shows: the cosine-to-angle helper
 * and the actor tick each take one argument, and Ghidra fills the rest in from
 * registers that merely happened to be live at the call. The two working arms
 * need separate scratch vectors - sharing one makes mwcc merge them and the
 * frame comes out twelve bytes short. And the two flag bits are cleared in two
 * statements, which is what gives the ROM's pair of bic instructions.
 */
void *Ov002_TickCamera(void)
{
    int nA;
    int nB;
    VecFx32 vAnchor;
    VecFx32 vDelta;
    VecFx32 vDirA;
    VecFx32 vDirB;
    VecFx32 vOriginA;
    VecFx32 vOriginB;
    VecFx32 vWork;
    VecFx32 vFlat;
    unsigned int nBits;
    int nScreenA;
    int nScreenB;
    char *pCam;
    void *pNext;
    int nPlayer;
    VecFx32 *pTarget;
    int nHandle;
    int *pObj;
    int nDist;
    int nBase;
    int nRatio;
    int nStep;
    int nAngle;
    int nTmp;
    int bHeld;

    pCam = (char *)NNSi_FndGetCurrentRootHeap();
    nPlayer = QueryActiveStateOrDelegate();
    pNext = 0;
    pTarget = (VecFx32 *)func_ov022_020881f8(nPlayer);
    nHandle = func_ov022_02083f5c();
    GetEntryField20ByIndex(nPlayer);
    nDist = Ov002_UpdateCameraDistance(*(int *)(pCam + 0x44));
    nBase = Ov002_UpdateCameraDistance(0);
    nRatio = FX_Div(nDist, nBase);

    if (data_0204be04 != *(unsigned int *)(pCam + 0xe0)) {
        return 0;
    }
    if ((*(unsigned int *)(pCam + 0x38) & 4) != 0) {
        return 0;
    }
    if (func_ov022_020881d8() != 0) {
        return 0;
    }
    if (func_ov022_02088338() == 0) {
        return 0;
    }

    if (Ov022_IsBit2SetVia0x20(nHandle) != 0) {
        *(unsigned int *)(pCam + 0x38) &= 0xfffffeff;
    }

    if ((Ov022_IsBit2SetVia0x20(nHandle) == 0
         && (*(unsigned int *)(pCam + 0x38) & 0x100) == 0)
        || pTarget == 0
        || func_ov022_020886d0(nPlayer) != 0
        || (*(unsigned int *)(pCam + 0x38) & 0x8000) != 0
        || (*(unsigned int *)(pCam + 0x38) & 0x20000000) != 0) {
        *(unsigned int *)(pCam + 0x38) &= 0xffffffdf;
        *(int *)(pCam + 0x84) = Ov002_Camera_GetPresetHeight(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x88) = Ov002_GetCameraDistance(*(int *)(pCam + 0x44));
        if (((gPadPressed & 4) != 0 && data_0204be04 == 0)
            || (data_0204be04 != 0 && *(int *)(pCam + 0xfc) != 0)) {
            *(unsigned int *)(pCam + 0x38) |= 0x2800;
            Ov002_ClearPendingOnBoot();
        }
        pNext = (void *)Ov002_Camera_UpdateFollow;
    } else if ((*(unsigned int *)(pCam + 0x38) & 0x40) != 0
               || (*(unsigned int *)(pCam + 0x38) & 0x80) != 0) {
        if ((*(unsigned int *)(pCam + 0x38) & 0x100) != 0) {
            pObj = (int *)(pCam + 0x8c);
        } else {
            pObj = func_ov022_020865b4();
        }
        vAnchor = *pTarget;
        if (pObj != 0) {
            bHeld = 0;
            if (Ov002_IsPointOnScreen(&nBits, pObj, 0, 0x28) == 0) {
                if (Ov002_IsAngleBeyondLimit(*(int *)(pCam + 0x58),
                                        *(int *)(pCam + 0x80)) == 0) {
                    nStep = FX_Div(*(int *)(pCam + 0x84), 0xa000);
                    if (nStep < 0) {
                        nStep = -nStep;
                    }
                    if ((nBits & 4) != 0
                        && FX_Mul(nRatio, -0x2000) < *(int *)(pCam + 0x84)) {
                        *(int *)(pCam + 0x84) -=
                            FX_Mul(*(int *)(pCam + 0xac) + nStep, 0x2800);
                    }
                    if ((nBits & 8) != 0
                        && FX_Mul(nRatio, 0x3400) > *(int *)(pCam + 0x84)) {
                        *(int *)(pCam + 0x84) +=
                            FX_Mul(*(int *)(pCam + 0xac) + nStep, 0x2800);
                    }
                }
            } else {
                bHeld = 1;
            }
            VEC_Subtract(pTarget, (VecFx32 *)pObj, &vDelta);
            vDelta.y = 0;
            if (VEC_Mag(&vDelta) != 0) {
                VEC_Normalize(&vDelta, &vDelta);
            }
            nAngle = FX_Atan2Idx(vDelta.x, vDelta.z);
            *(int *)(pCam + 0x80) =
                Ov002_TurnAngleToward(*(int *)(pCam + 0x80), nAngle);
            if ((*(unsigned int *)(pCam + 0x38) & 0x100) == 0
                && (Ov002_IsAngleBeyondLimit(*(int *)(pCam + 0x58), nAngle) == 0
                    || Ov002_IsPointOnScreen(&nBits, pObj, 0x50, 0) != 0)
                && bHeld) {
                *(unsigned int *)(pCam + 0x38) &= 0xffffffbf;
                *(unsigned int *)(pCam + 0x38) &= 0xffffff7f;
            }
            nTmp = Ov002_UpdateCameraDistance(*(int *)(pCam + 0x44));
            Ov002_PlaceCameraForFrame((VecFx32 *)(pCam + 0x70),
                                (VecFx32 *)(pCam + 0x64),
                                (int *)(pCam + 0x7c), &vAnchor,
                                *(int *)(pCam + 0x58), nTmp,
                                *(int *)(pCam + 0x7c));
            Ov002_TickCameraTransition(Obj_GetCurrent());
        }
    } else {
        pObj = func_ov022_020865b4();
        if (pObj != 0) {
            if (Ov002_IsPointOnScreen(&nBits, pObj, 0, 0x28) == 0) {
                nStep = FX_Div(*(int *)(pCam + 0x84), 0xa000);
                if (nStep < 0) {
                    nStep = -nStep;
                }
                if ((nBits & 4) != 0
                    && FX_Mul(nRatio, -0x2000) < *(int *)(pCam + 0x84)) {
                    *(int *)(pCam + 0x84) -=
                        FX_Mul(*(int *)(pCam + 0xac) + nStep, 0x300);
                }
                if ((nBits & 8) != 0
                    && FX_Mul(nRatio, 0x3400) > *(int *)(pCam + 0x84)) {
                    *(int *)(pCam + 0x84) +=
                        FX_Mul(*(int *)(pCam + 0xac) + nStep, 0x300);
                }
            } else if (Ov002_IsPointOnScreen(&nBits, pObj, 0, 0x50) != 0) {
                nTmp = Ov002_Camera_GetPresetHeight(*(int *)(pCam + 0x44))
                       - *(int *)(pCam + 0x84);
                nTmp = FX_Mul(nTmp, 0xc0);
                nA = nTmp < 0 ? -nTmp : nTmp;
                if (nA < 0x10) {
                    *(int *)(pCam + 0x84) =
                        Ov002_Camera_GetPresetHeight(*(int *)(pCam + 0x44));
                } else {
                    *(int *)(pCam + 0x84) += nTmp;
                }
                *(int *)(pCam + 0x88) =
                    Ov002_GetCameraDistance(*(int *)(pCam + 0x44));
            }
            if (Ov002_IsPointOnScreen(&nBits, pObj, 0x50, 0) == 0) {
                nAngle = *(int *)(pCam + 0x58);
                func_0201653c(pObj, &nScreenA, &nScreenB);
                func_020166c4(nScreenA, nScreenB, (int *)&vDirA,
                              (int *)&vOriginA);
                if ((nBits & 2) != 0) {
                    nScreenA = 0xaf;
                }
                if ((nBits & 1) != 0) {
                    nScreenA = 0x50;
                }
                nScreenB = 0;
                func_020166c4(nScreenA, 0, (int *)&vDirB, (int *)&vOriginA);
                vOriginB = data_020475ac;
                VEC_Subtract(&vDirB, &vOriginB, &vWork);
                vWork.y = 0;
                VEC_Normalize(&vWork, &vWork);
                VEC_Subtract(&vDirA, &vOriginB, &vFlat);
                vFlat.y = 0;
                VEC_Normalize(&vFlat, &vFlat);
                nB = VEC_DotProduct(&vWork, &vFlat);
                if ((nBits & 2) != 0) {
                    nAngle = (*(int *)(pCam + 0x58)
                              - FX_AcosIdx(nB)) & 0xffff;
                }
                if ((nBits & 1) != 0) {
                    nAngle = (*(int *)(pCam + 0x58)
                              + FX_AcosIdx(nB)) & 0xffff;
                }
                *(int *)(pCam + 0x80) = nAngle;
                if (Ov002_IsPointOnScreen(&nBits, pObj, 0x20, 0x20) == 0) {
                    *(unsigned int *)(pCam + 0x38) |= 0x80;
                }
            }
            nTmp = Ov002_UpdateCameraDistance(*(int *)(pCam + 0x44));
            Ov002_PlaceCameraForFrame((VecFx32 *)(pCam + 0x70),
                                (VecFx32 *)(pCam + 0x64),
                                (int *)(pCam + 0x7c), pTarget,
                                *(int *)(pCam + 0x58), nTmp,
                                *(int *)(pCam + 0x7c));
            Ov002_TickCameraTransition(Obj_GetCurrent());
        }
    }
    return pNext;
}
