typedef struct {
    int x, y, z;
} VecFx32;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int nPlayer);
extern void *func_01fffde0(int nPlayer);
extern int func_ov002_02072754(int nWorldId);
extern int func_ov002_02072964(int nSlot);
extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff8d18(const VecFx32 *v, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(int k, const VecFx32 *a, const VecFx32 *b,
                        VecFx32 *out);
extern int VEC_Mag(const VecFx32 *v);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int func_ov002_0204e864(VecFx32 *pStart, VecFx32 *pMotion,
                               VecFx32 *pHitPos, VecFx32 *pOutNormal,
                               void *pExclude);
extern int func_ov002_0204e6e0(VecFx32 *pStart, VecFx32 *pMotion,
                               VecFx32 *pHitPos, VecFx32 *pOutNormal,
                               void *pExclude);
extern int func_ov002_0204e9e8(VecFx32 *pOrigin, VecFx32 *pDir,
                               VecFx32 *pOutContact, void *pExclude);

/* Pull the camera in until nothing sits between it and what it is looking at.
 *
 * Three casts run from the focus point toward the wanted camera position: the
 * ray, the sphere sweep and the plain contact query. Whichever reports the
 * nearest surface -- nearer than the shot itself -- wins, and the camera moves
 * to it. If none of them hits, one more ray runs the other way, from the wanted
 * position back toward the focus, to catch a camera that starts inside geometry.
 *
 * What follows is the vertical pass. A ceiling comes from the world's own limit,
 * lowered by anything hanging just above the camera, and the camera is clamped
 * under it. Then a ray straight down decides whether the camera is standing too
 * close to the floor, in which case it is lifted one 0xc00 clearance along the
 * surface normal. Finally, unless the context asks to skip it, a camera that has
 * ended up almost on top of the focus in the horizontal plane is pushed back out
 * to 0xc00 from it.
 *
 * The out-of-world early exit returns nothing at all: it is a bare `return;`,
 * which mwcc accepts here and which is why no return register is written on that
 * path. That is what the ROM does; giving it a value costs an instruction.
 */
int func_ov002_0204ea58(VecFx32 *pOutFocus, VecFx32 *pOutCamera,
                        VecFx32 *pFocus, VecFx32 *pCamera)
{
    VecFx32 vContact;
    VecFx32 vDir;
    VecFx32 vNormal;
    VecFx32 vCam;
    VecFx32 vFocus;
    VecFx32 vToCam;
    VecFx32 vProbe;
    VecFx32 vFlat;
    VecFx32 vCamFlat;
    VecFx32 vFocusFlat;
    VecFx32 vPush;
    int bDirect;
    int nResult;
    void *pCtx;
    void *pExclude;
    int nPlayer;
    int nWorldId;
    int bHit;
    int nBest;
    int nDist;
    int nCeil;
    int nLen;

    pCtx = NNSi_FndGetCurrentRootHeap();
    nPlayer = func_01fffe14();
    nWorldId = func_ov022_02088474(nPlayer);
    pExclude = 0;
    vCam = *pCamera;
    bHit = 0;
    bDirect = 0;
    vFocus = *pFocus;
    nResult = 0;
    if (nPlayer < 0 || nWorldId < 0) {
        return;
    }

    if (func_01fffde0(nPlayer) != 0) {
        pExclude = *(void **)((char *)func_01fffde0(nPlayer) + 0x20);
    }

    vContact.z = 0;
    vContact.y = 0;
    vContact.x = 0;
    nBest = 0x7fffffff;
    VEC_Subtract(pCamera, pFocus, &vDir);

    if (func_ov002_0204e864(pFocus, &vDir, &vContact, &vNormal, pExclude)
        != 0) {
        nDist = func_01ff8e94(pFocus, &vContact);
        if (nDist < nBest && nDist < VEC_Mag(&vDir)) {
            vCam = vContact;
            bHit = 1;
            nBest = nDist;
        }
    }

    if (func_ov002_0204e6e0(pFocus, &vDir, &vContact, &vNormal, pExclude)
        != 0) {
        nDist = func_01ff8e94(pFocus, &vContact);
        if (nDist < nBest && nDist < VEC_Mag(&vDir)) {
            vCam = vContact;
            bHit = 1;
            nBest = nDist;
        }
    }

    if (func_ov002_0204e9e8(pFocus, &vDir, &vContact, pExclude) != 0) {
        nDist = func_01ff8e94(pFocus, &vContact);
        if (nDist < nBest && nDist < VEC_Mag(&vDir)) {
            bHit = 1;
            vCam = vContact;
            bDirect = 1;
        }
    }

    if (!bHit) {
        VEC_Subtract(pFocus, pCamera, &vDir);
        if (func_ov002_0204e864(pCamera, &vDir, &vContact, &vNormal, pExclude)
            != 0) {
            nLen = VEC_Mag(&vDir);
            nDist = func_01ff8e94(pCamera, &vContact);
            if (nLen > nDist) {
                vCam = vContact;
                bHit = 1;
            }
        }
    }

    if (bHit) {
        VEC_Subtract(&vCam, (VecFx32 *)((char *)pCtx + 0x20), &vToCam);
        VEC_Subtract(pFocus, pCamera, &vDir);
        if (VEC_Mag(&vToCam) > 0x3000
            && VEC_DotProduct(&vToCam, &vDir) > 0) {
            *(int *)((char *)pCtx + 0x9c) = 1;
        }
    }

    nCeil = func_ov002_02072964(func_ov002_02072754(nWorldId));
    vDir.x = 0;
    vDir.y = 0xa000;
    vDir.z = 0;
    vProbe.x = vCam.x;
    vProbe.y = vCam.y - 0x800;
    vProbe.z = vCam.z;
    if (bDirect) {
        if (nCeil > vProbe.y) {
            nCeil = vProbe.y;
        }
    } else {
        if (func_ov002_0204e9e8(&vProbe, &vDir, &vContact, pExclude) != 0
            && vContact.y - vCam.y < 0xc00) {
            if (nCeil > vContact.y - 0xc00) {
                nCeil = vContact.y - 0xc00;
            }
        }
    }
    if (nCeil < vCam.y) {
        vCam.y = nCeil;
    }

    vDir.x = 0;
    vDir.y = -0xa000;
    vDir.z = 0;
    vProbe.x = vCam.x;
    vProbe.y = vCam.y + 0x800;
    vProbe.z = vCam.z;
    if (func_ov002_0204e864(&vProbe, &vDir, &vContact, &vNormal, pExclude)
        != 0) {
        nDist = func_01ff8e94(&vCam, &vContact);
        VEC_Subtract(&vCam, &vContact, &vFlat);
        func_01ff8d18(&vFlat, &vFlat);
        if (nDist < 0xc00 || VEC_DotProduct(&vFlat, &vNormal) < 0) {
            VEC_MultAdd(0xc00, &vNormal, &vContact, &vCam);
        }
    }

    if ((*(unsigned int *)((char *)pCtx + 0x38) & 0x1000000) == 0) {
        vCamFlat = vCam;
        vFocusFlat = *pFocus;
        vCamFlat.y = 0;
        vFocusFlat.y = 0;
        if (func_01ff8e94(&vCamFlat, &vFocusFlat) < 0xc00) {
            VEC_Subtract(pCamera, pFocus, &vPush);
            func_01ff8d18(&vPush, &vPush);
            VEC_MultAdd(0xc00, &vPush, pFocus, &vCam);
            if (nCeil < vCam.y) {
                vCam.y = nCeil;
            }
        }
        nResult = 1;
    }

    *pOutCamera = vCam;
    *pOutFocus = vFocus;
    return nResult;
}
