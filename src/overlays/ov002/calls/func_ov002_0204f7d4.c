typedef struct {
    int x, y, z;
} VecFx32;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern int *func_01fffde0(int nPlayer);
extern void *func_02023bf0(void);   /* the active scene */
extern int func_02023c40(void);     /* frame-rate flag */
extern int func_02030670(void);     /* session active */

extern int *func_ov022_020881f8(int nPlayer);
extern int func_ov022_02083f5c(void);
extern int func_ov022_020881d8(void);
extern int func_ov022_02088338(void);
extern int func_ov022_020886d0(int nPlayer);
extern int func_ov022_02088254(int nPlayer);

extern void func_ov002_0204d170(void);
extern int func_ov002_0204e474(int nAngleA, int nAngleB);
extern void func_ov002_0204eee0(VecFx32 *pOutFocus, VecFx32 *pOutCamera,
                                int *pOutDist, VecFx32 *pAnchor, int nAngle,
                                int nDist, int nPrevDist);
extern void func_ov002_0204ff18(void *pScene);
extern int func_ov002_02050a54(int nSelector);
extern int func_ov002_02050b68(int nSelector);
extern int func_ov002_02050b90(int nSelector);

extern unsigned char data_0204be04;
extern short data_0203d210[];   /* angle sin/cos table, 4 bytes per entry */

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

/* Scripted camera tick: the state machine that runs while the camera is under
 * a cut or a forced pose rather than following the player.
 *
 * Same gate as the ordinary tick - the stage id at +0xe0 must agree with the
 * global one, flag bit 4 must be clear and the session must be up. When the
 * session reports a handover it jumps straight to state 5.
 *
 * State 0 chooses a distance table row from the player entry's kind: rows 0xc,
 * 0xd, 0xe and 0xf, with the old row saved at +0x48 so the later states can put
 * it back. Then the frame timer at +0xdc advances by 0xcd or 0x89 depending on
 * the frame-rate flag, clamped at zero.
 *
 * States 1 and 3 hold the new distance and wait for either the timer to pass
 * 0xcc or the distance to cross the threshold at +0x54 - 1 waits for it to
 * close, 3 for it to open. State 2 swings the yaw round by 0x64 a frame until
 * the timer passes 0x668, doubled while the session is idle. State 4 is the
 * scripted pose: it reads the entry's own angle, and for kind 2 pushes the
 * anchor back along it before setting the yaw, or for kind 9 just takes the
 * angle. State 5 releases the camera and hands back the ordinary handler.
 *
 * Five shapes carry the codegen. The four switch groups come out in source
 * order, so they are written 0xc, 0xd, 0xe, 0xf. The frame timer is computed
 * into a scalar and stored once rather than stored in both arms. The distance
 * refresh after the row copy reads the field it just wrote, which mwcc forwards
 * instead of reloading. The two-kind test in state 4 is a SWITCH with case 2
 * first - the only shape that both places the case-2 body out of line and
 * predicates the case-9 one. And the flattened anchor is read into three
 * scalars and written back as three, which is what puts the untouched Y
 * component's load and store back in.
 */
void *func_ov002_0204f7d4(void)
{
    VecFx32 vAnchor;
    char *pCam;
    void *pNext;
    int nPlayer;
    int *pEntry;
    int *pTarget;
    int nAngle;
    int nSin;
    int nCos;
    int nLimit;
    int nYaw;
    int nStep;
    int nTimer;
    int nX;
    int nY;
    int nZ;

    pCam = (char *)NNSi_FndGetCurrentRootHeap();
    pNext = 0;
    nPlayer = func_01fffe14();
    pEntry = func_01fffde0(nPlayer);
    pTarget = func_ov022_020881f8(nPlayer);
    func_ov022_02083f5c();
    vAnchor = *(VecFx32 *)pTarget;

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

    if (func_ov022_020886d0(nPlayer) != 0) {
        *(int *)(pCam + 0x44) = *(int *)(pCam + 0x48);
        *(int *)(pCam + 0x7c) = func_ov002_02050b90(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x84) = func_ov002_02050b68(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x88) = func_ov002_02050a54(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x4c) = 5;
    }

    if (*(int *)(pCam + 0x4c) == 0) {
        *(int *)(pCam + 0xdc) = 0;
        *(int *)(pCam + 0x48) = *(int *)(pCam + 0x44);
        switch (pEntry[3]) {
        case 16:
        case 17:
            *(int *)(pCam + 0x44) = 0xc;
            break;
        case 0:
        case 5:
        case 11:
        case 14:
        case 19:
        case 20:
        case 21:
            *(int *)(pCam + 0x44) = 0xd;
            break;
        case 1:
        case 2:
        case 3:
        case 6:
        case 7:
        case 9:
        case 10:
        case 15:
        case 18:
            *(int *)(pCam + 0x44) = 0xe;
            break;
        case 4:
        case 8:
        case 12:
        case 13:
            *(int *)(pCam + 0x44) = 0xf;
            break;
        }
        *(int *)(pCam + 0x4c) = 1;
    }

    func_02023c40();
    nTimer = *(int *)(pCam + 0xdc)
             + (func_02023c40() == 1 ? 0xcd : 0x89);
    if (nTimer < 0) {
        nTimer = 0;
    } else {
        nTimer = *(int *)(pCam + 0xdc)
                 + (func_02023c40() == 1 ? 0xcd : 0x89);
    }
    *(int *)(pCam + 0xdc) = nTimer;

    switch (*(int *)(pCam + 0x4c)) {
    case 1:
        *(int *)(pCam + 0x7c) = func_ov002_02050b90(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x84) = func_ov002_02050b68(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x88) = func_ov002_02050a54(*(int *)(pCam + 0x44));
        if (*(int *)(pCam + 0xdc) > 0xcc
            || *(int *)(pCam + 0x54) <= *(int *)(pCam + 0x7c)) {
            *(int *)(pCam + 0x4c) = 2;
            *(int *)(pCam + 0xdc) = 0;
        }
        break;
    case 2:
        nLimit = 0x668;
        nYaw = (*(int *)(pCam + 0x80) + 0x64) & 0xffff;
        if (func_02030670() == 0) {
            nLimit <<= 1;
        }
        *(int *)(pCam + 0x80) =
            func_ov002_0204e474(*(int *)(pCam + 0x80), nYaw);
        if (nLimit < *(int *)(pCam + 0xdc)) {
            *(int *)(pCam + 0x4c) = 3;
            *(int *)(pCam + 0x44) = *(int *)(pCam + 0x48);
            *(int *)(pCam + 0xdc) = 0;
        }
        break;
    case 3:
        *(int *)(pCam + 0x7c) = func_ov002_02050b90(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x84) = func_ov002_02050b68(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x88) = func_ov002_02050a54(*(int *)(pCam + 0x44));
        if (*(int *)(pCam + 0xdc) > 0xcc
            || *(int *)(pCam + 0x54) >= *(int *)(pCam + 0x7c)) {
            *(int *)(pCam + 0x4c) = 5;
        }
        break;
    case 4:
        nAngle = func_ov022_02088254(nPlayer);
        nSin = data_0203d210[(nAngle >> 4) * 2];
        nCos = data_0203d210[(nAngle >> 4) * 2 + 1];
        switch (pEntry[3]) {
        case 2:
            nZ = vAnchor.z - FX_Mul(nCos, 0x2000);
            nY = vAnchor.y;
            nX = vAnchor.x - FX_Mul(nSin, 0x2000);
            vAnchor.x = nX;
            vAnchor.y = nY;
            vAnchor.z = nZ;
            *(int *)(pCam + 0x80) = (nAngle - 0x3e8) & 0xffff;
            break;
        case 9:
            *(int *)(pCam + 0x80) = nAngle & 0xffff;
            break;
        }
        if ((*(unsigned long long *)((char *)pEntry + 0x464) & 0x10000ULL) == 0
            || (*(unsigned int *)(pCam + 0x38) & 0x20000000) == 0) {
            *(int *)(pCam + 0x44) = *(int *)(pCam + 0x48);
            *(int *)(pCam + 0x4c) = 5;
            *(unsigned int *)(pCam + 0x38) &= 0xdfffffff;
        }
        *(int *)(pCam + 0x7c) = func_ov002_02050b90(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x84) = func_ov002_02050b68(*(int *)(pCam + 0x44));
        *(int *)(pCam + 0x88) = func_ov002_02050a54(*(int *)(pCam + 0x44));
        break;
    case 5:
        *(unsigned int *)(pCam + 0x38) &= 0xffff7fff;
        *(int *)(pCam + 0x40) = 0;
        pNext = (void *)func_ov002_0204d170;
        *(int *)(pCam + 0xdc) = 0;
        break;
    }

    nStep = func_ov002_02050b90(*(int *)(pCam + 0x44));
    func_ov002_0204eee0((VecFx32 *)(pCam + 0x70), (VecFx32 *)(pCam + 0x64),
                        (int *)(pCam + 0x7c), &vAnchor,
                        *(int *)(pCam + 0x80), nStep,
                        *(int *)(pCam + 0x7c));
    func_ov002_0204ff18(func_02023bf0());
    return pNext;
}
