typedef struct {
    int x, y, z;
} VecFx32;

extern int func_01fffe14(void);
extern int *func_01fffde0(int nPlayer);
extern int func_02023c40(void);     /* frame-rate flag */
extern int func_020208e0(void);
extern int func_02030788(void);
extern void func_02016d10(int nModel, int nValue);
extern int FX_Sqrt(int v);
extern int FX_Inv(int a, int b);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff8d18(const VecFx32 *v, VecFx32 *out);   /* normalise */
extern int VEC_Mag(const VecFx32 *v);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(int k, const VecFx32 *a, const VecFx32 *b,
                        VecFx32 *out);

extern VecFx32 *func_ov022_020881f8(int nPlayer);
extern int func_ov022_02088254(int nPlayer);
extern void func_ov022_02088314(int nPlayer);

extern unsigned short data_0204c190;
extern short data_0203d210[];   /* angle sin/cos table, 4 bytes per entry */
extern int data_ov002_0207e734[];
extern int data_ov002_0207e73c[];

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

/* Actor tick: settle every camera field toward the value this frame asked for.
 */
typedef struct {
    char pad00[20];
    VecFx32 vFocus;
    VecFx32 vEyePos;
    char pad01[12];
    unsigned int nFlags;
    char pad02[4];
    int nHoldTicks;
    char pad03[8];
    int nScriptState;
    char pad04[4];
    int nDist;
    int nYaw;
    int nEyeHeight;
    int nFocusGroundOffset;
    char pad05[4];
    int nAnchorY;
    char pad06[4];
    VecFx32 vOutFocus;
    int nTargetDist;
    int nTargetYaw;
    int nTargetEyeHeight;
    int nTargetFocusGroundOffset;
    char pad07[16];
    int bJustReset;
    char pad08[4];
    int nFocusApproachThreshold;
    int nYawSlewThreshold;
    char pad09[4];
    int nFocusApproachRateOverride;
    int nFadeTarget;
    int nFadeLevel;
    int nShakeAmount;
    int nShakePhase;
    int bShakeFlip;
    int nShakeEnergy;
    int nShakeRow;
    char pad0a[12];
    int nScriptTimer;
    char pad0b[32];
} CameraState;

int func_ov002_0204ff18(void *pScene)
{
    VecFx32 vToTarget;
    VecFx32 vDir;
    VecFx32 vEye;
    VecFx32 vDelta;
    VecFx32 vShakeDir;
    VecFx32 vShakeAxis;
    CameraState *pCam;
    int nPlayer;
    VecFx32 *pTarget;
    int *pEntry;
    int nLimit;
    int nRate;
    int nTarget;
    int nDelta;
    int nMove;
    int nAbs;
    int nStep;
    int nApply;
    int nAngle;
    int nIdx;
    int nHeight;
    int nLeg;
    int nRadius;
    int nYaw;
    int nDiff;
    int nTimer;
    int nApproach;
    int nDist;
    int nVal;
    int bStep;
    int nSum;
    int nX;
    int nY;
    int nZ;

    pCam = *(CameraState **)((char *)pScene + 0x20);
    nPlayer = func_01fffe14();
    pTarget = func_ov022_020881f8(nPlayer);
    pEntry = func_01fffde0(nPlayer);

    nLimit = FX_Mul(func_02023c40() == 1 ? 0xc00 : 0x800, 0x10000);
    if ((pCam->nFlags & 0x20) != 0) {
        nLimit = FX_Mul(nLimit, 0x4000);
    }
    if (pCam->nFocusApproachThreshold > nLimit) {
        nLimit = func_02023c40() == 1 ? 0xc00 : 0x800;
    }

    nTarget = pCam->nTargetEyeHeight;
    if (pCam->nEyeHeight != nTarget) {
        nDelta = nTarget - pCam->nEyeHeight;
        nAbs = nDelta < 0 ? -nDelta : nDelta;
        if (nAbs <= 0x100) {
            pCam->nEyeHeight = nTarget;
        } else {
            nRate = func_02023c40() == 1 ? 0x900 : 0x600;
            pCam->nEyeHeight = pCam->nEyeHeight
                                    + FX_Mul(nDelta, nRate);
        }
    }

    nTarget = pCam->nTargetFocusGroundOffset;
    if (pCam->nFocusGroundOffset != nTarget) {
        nDelta = nTarget - pCam->nFocusGroundOffset;
        nAbs = nDelta < 0 ? -nDelta : nDelta;
        if (nAbs <= 0x100) {
            pCam->nFocusGroundOffset = nTarget;
        } else {
            nRate = func_02023c40() == 1 ? 0x900 : 0x600;
            pCam->nFocusGroundOffset = pCam->nFocusGroundOffset
                                    + FX_Mul(nDelta, nRate);
        }
    }

    nTarget = pCam->nFadeTarget;
    if (pCam->nFadeLevel != nTarget) {
        nDelta = (nTarget - pCam->nFadeLevel) * 0x1000;
        nAbs = nDelta < 0 ? -nDelta : nDelta;
        if (nAbs < 0x4000) {
            pCam->nFadeLevel = nTarget;
        } else {
            nStep = FX_Mul(nDelta, 0xc00) >> 12;
            nApply = (unsigned short)nStep;
            if (nDelta > 0) {
                pCam->nFadeLevel = pCam->nFadeLevel + nApply;
            } else {
                pCam->nFadeLevel = pCam->nFadeLevel - nApply;
            }
        }

        nVal = pCam->nFadeTarget;
        if (nVal > 0x1f) {
            nVal = 0x1f;
        } else if (nVal < 0) {
            nVal = 0;
        }
        pCam->nFadeTarget = nVal;

        nVal = pCam->nFadeLevel;
        if (nVal > 0x1f) {
            nVal = 0x1f;
        } else if (nVal < 0) {
            nVal = 0;
        }
        pCam->nFadeLevel = nVal;

        func_02016d10(*(int *)(*(int *)((char *)pEntry + 0x20) + 0x7c), nVal);
    }

    nTarget = pCam->nTargetDist;
    if (pCam->nDist != nTarget) {
        nMove = nTarget - pCam->nDist;
        nAbs = nMove < 0 ? -nMove : nMove;
        if (nAbs < 0x100) {
            pCam->nDist = nTarget;
        } else {
            bStep = 0;
            if (pCam->bJustReset != 0) {
                if (pTarget == 0 || pEntry == 0
                    || func_01ff8e94(pTarget,
                                     (VecFx32 *)((char *)pEntry + 0x48c))
                       > 0x100) {
                    pCam->nDist = pCam->nTargetDist;
                } else {
                    bStep = 1;
                }
            } else {
                bStep = 1;
            }

            if (bStep) {
                nDiff = (pCam->nYaw - pCam->nTargetYaw)
                        & 0xffff;
                if (pCam->nDist < pCam->nTargetDist) {
                    nRate = 0x400;
                } else if (pCam->nYawSlewThreshold < 0x400 && nDiff < 0xfa0) {
                    nRate = 0x800;
                } else if (pCam->nYawSlewThreshold < 0x59a && nDiff < 5000) {
                    nRate = 0xc00;
                } else {
                    nRate = 0x1000;
                }
                nStep = FX_Mul(nMove, nRate);
                nApply = nAbs;
                if (nStep <= nAbs) {
                    nApply = -nAbs;
                    if (nStep >= -nAbs) {
                        nApply = nStep;
                    }
                }
                pCam->nDist = pCam->nDist + nApply;
            }
        }
    }

    vEye = pCam->vEyePos;

    if ((pCam->nFlags & 0x10000) != 0) {
        nAngle = func_ov022_02088254(nPlayer);
        nIdx = nAngle >> 4;
        nZ = pCam->vFocus.z
             + FX_Mul(data_0203d210[nIdx * 2 + 1], pCam->nDist);
        nY = pCam->vFocus.y + pCam->nEyeHeight;
        nX = pCam->vFocus.x
             + FX_Mul(data_0203d210[nIdx * 2], pCam->nDist);
        vEye.x = nX;
        vEye.y = nY;
        vEye.z = nZ;
        VEC_Subtract(&vEye, &pCam->vFocus, &vDir);
        func_01ff8d18(&vDir, &vDir);
        VEC_MultAdd(pCam->nDist, &vDir, &pCam->vFocus,
                    &vEye);
        pCam->vEyePos = vEye;
        if (func_020208e0() != 2 || func_02030788() != 0) {
            if ((data_0204c190 & 0x40) != 0) {
                pCam->nTargetYaw = nAngle;
                pCam->nYaw = nAngle;
            }
        }
    } else {
        nDelta = pCam->nAnchorY - pCam->vEyePos.y;
        if (pCam->bJustReset == 0) {
            nDelta = FX_Mul(nDelta, 0xc00);
        }
        nAbs = nDelta < 0 ? -nDelta : nDelta;
        if (nAbs > 0x52) {
            vEye.y = vEye.y + nDelta;
        } else {
            vEye.y = pCam->nAnchorY;
        }

        nHeight = pCam->vEyePos.y - pCam->vFocus.y;
        nRadius = pCam->nDist;
        nLeg = FX_Sqrt(FX_Mul(nRadius, nRadius) - FX_Mul(nHeight, nHeight));
        nRadius = pCam->nDist;
        if (nLeg <= pCam->nDist) {
            if (nLeg < 0xc00) {
                nLeg = 0xc00;
            }
            nRadius = nLeg;
        }

        nIdx = pCam->nYaw >> 4;
        nZ = pCam->vFocus.z
             + FX_Mul(data_0203d210[nIdx * 2 + 1], nRadius);
        nY = vEye.y;
        nX = pCam->vFocus.x + FX_Mul(data_0203d210[nIdx * 2], nRadius);
        vEye.x = nX;
        vEye.y = nY;
        vEye.z = nZ;
        VEC_Subtract(&vEye, &pCam->vFocus, &vDir);
        func_01ff8d18(&vDir, &vDir);
        VEC_MultAdd(pCam->nDist, &vDir, &pCam->vFocus,
                    &vEye);
        VEC_Subtract(&vEye, &pCam->vEyePos, &vDelta);
        pCam->vEyePos = vEye;
    }

    if ((*(unsigned long long *)((char *)pEntry + 0x464) & 0x400000000ULL)
        == 0) {
        if ((pCam->nFlags & 0x10000) != 0
            || pCam->nScriptState == 4) {
            pCam->vFocus = pCam->vOutFocus;
        } else {
            func_ov022_02088314(func_01fffe14());
            if ((pCam->nFlags & 0x2000000) != 0) {
                nApproach = pCam->nFocusApproachRateOverride;
            } else if (func_02023c40() == 1) {
                nApproach = 0x480;
            } else {
                nApproach = 0x300;
            }
            if (nLimit - 0x200 < pCam->nFocusApproachThreshold) {
                nApproach = nLimit - 0x200;
            }

            VEC_Subtract(&pCam->vOutFocus, &pCam->vFocus,
                         &vToTarget);
            nDelta = vToTarget.y;
            vToTarget.y = 0;
            nDist = VEC_Mag(&vToTarget);
            if (nDist > 0x10) {
                nStep = FX_Mul(nDist, nApproach);
                if (nStep <= nDist) {
                    if (nStep < 0) {
                        nStep = 0;
                    }
                    nDist = nStep;
                }
                func_01ff8d18(&vToTarget, &vToTarget);
                VEC_MultAdd(nDist, &vToTarget, &pCam->vFocus,
                            &pCam->vFocus);
            } else {
                pCam->vFocus.x = pCam->vOutFocus.x;
                pCam->vFocus.z = pCam->vOutFocus.z;
            }

            nAbs = nDelta < 0 ? -nDelta : nDelta;
            if (nAbs > 0x10) {
                if ((pCam->nFlags & 0x2000000) != 0) {
                    nApproach = func_02023c40() == 1 ? 0x90 : 0x60;
                } else {
                    nApproach = func_02023c40() == 1 ? 0x900 : 0x600;
                }
                if (nDelta > 0) {
                    nStep = FX_Mul(nDelta, nApproach);
                    if (nStep <= nDelta) {
                        if (nStep < 0) {
                            nStep = 0;
                        }
                        nDelta = nStep;
                    }
                } else {
                    nStep = FX_Mul(nDelta, nApproach);
                    if (nStep > 0) {
                        nDelta = 0;
                    } else if (nStep >= nDelta) {
                        nDelta = nStep;
                    }
                }
                pCam->vFocus.y = pCam->vFocus.y + nDelta;
            } else {
                pCam->vFocus.y = pCam->vOutFocus.y;
            }
        }
    }

    if (pCam->nYaw != pCam->nTargetYaw) {
        nRate = 0x800;
        if ((pCam->nFlags & 0x20) != 0) {
            nRate = 0x400;
        }
        if (pCam->nScriptState == 4) {
            nRate = 0xd00;
        }
        if ((pCam->nFlags & 0x20008000) == 0) {
            nTimer = pCam->nScriptTimer;
            if (nTimer > 0x333) {
                nRate = FX_Mul(FX_Inv(nTimer - 0x333, 0x1000 - 0x333), 0x600)
                        + 0x200;
                if (nRate > 0x800) {
                    nRate = 0x800;
                } else if (nRate < 0x200) {
                    nRate = 0x200;
                }
            } else if (nTimer > 0) {
                nRate = 0x200;
            }
        }

        pCam->nTargetYaw = pCam->nTargetYaw & 0xffff;
        pCam->nYaw = pCam->nYaw & 0xffff;
        nYaw = pCam->nYaw;
        if (pCam->nTargetYaw < nYaw) {
            nDiff = nYaw - pCam->nTargetYaw;
            if (nDiff >= 0 && nDiff > 0xc000) {
                pCam->nYaw =
                    (nYaw + FX_Mul((-nDiff) & 0xffff, nRate)) & 0xffff;
            } else {
                pCam->nYaw =
                    (nYaw - FX_Mul(nDiff & 0xffff, nRate)) & 0xffff;
            }
        } else {
            nDiff = pCam->nTargetYaw - nYaw;
            if (nDiff >= 0 && nDiff > 0xc000) {
                pCam->nYaw =
                    (nYaw - FX_Mul((-nDiff) & 0xffff, nRate)) & 0xffff;
            } else {
                pCam->nYaw =
                    (nYaw + FX_Mul(nDiff & 0xffff, nRate)) & 0xffff;
            }
        }
    }

    if (pCam->nHoldTicks == 3) {
        if (pCam->bShakeFlip != 0) {
            nDelta = pCam->nShakeEnergy - pCam->nShakeAmount;
        } else {
            nDelta = -(pCam->nShakeEnergy + pCam->nShakeAmount);
        }
        pCam->nShakeAmount = pCam->nShakeAmount
                                + FX_Mul(nDelta, 0x800);

        if (*(int *)((char *)data_ov002_0207e73c
                     + pCam->nShakeRow * 0xc)
            < pCam->nShakePhase) {
            pCam->bShakeFlip = pCam->bShakeFlip == 0;
            pCam->nShakePhase = 0;
            pCam->nShakeEnergy =
                pCam->nShakeEnergy
                - *(int *)((char *)data_ov002_0207e734
                           + pCam->nShakeRow * 0xc);
        }
        pCam->nShakePhase = pCam->nShakePhase
                                + (func_02023c40() == 1 ? 0xcd : 0x89);

        VEC_Subtract(&pCam->vEyePos, &pCam->vFocus,
                     &vShakeDir);
        if (VEC_Mag(&vShakeDir) != 0) {
            func_01ff8d18(&vShakeDir, &vShakeDir);
        }
        nSum = FX_Mul(vShakeDir.x, vShakeDir.x)
               + FX_Mul(vShakeDir.z, vShakeDir.z);
        if (nSum != 0) {
            nStep = FX_Sqrt(FX_Inv(FX_Mul(vShakeDir.z, vShakeDir.z), nSum));
            nApply = FX_Sqrt(FX_Inv(FX_Mul(vShakeDir.x, vShakeDir.x), nSum));
            vShakeAxis.y = 0;
            vShakeAxis.x = nStep;
            vShakeAxis.z = -nApply;
            VEC_MultAdd(pCam->nShakeAmount, &vShakeAxis,
                        &pCam->vEyePos, &pCam->vEyePos);
            VEC_MultAdd(pCam->nShakeAmount, &vShakeAxis,
                        &pCam->vFocus, &pCam->vFocus);
        }
        if (pCam->nShakeEnergy < 0x29) {
            pCam->nShakeAmount = 0;
            pCam->nShakePhase = 0;
            pCam->nHoldTicks = 0;
        }
    }

    pCam->bJustReset = 0;
    return 1;
}
