typedef struct {
    int x, y, z;
} VecFx32;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern void *func_02023bf0(void);   /* the active scene */

extern VecFx32 *func_ov022_020881f8(void);
extern int func_ov022_02083f5c(void);
extern int func_ov022_020881d8(void);
extern int func_ov022_02088338(void);
extern int func_ov022_02086620(int nHandle);
extern int func_ov022_020886d0(int nPlayer);
extern int func_ov022_02088254(int nPlayer);

extern void func_ov002_0204d170(void);
extern int func_ov002_0204e414(int nAngleA, int nAngleB);
extern int func_ov002_0204e474(int nAngleA, int nAngleB);
extern void func_ov002_0204eee0(VecFx32 *pOutFocus, VecFx32 *pOutCamera,
                                int *pOutDist, VecFx32 *pAnchor, int nAngle,
                                int nDist, int nPrevDist);
extern void func_ov002_0204ff18(void *pScene);
extern int func_ov002_02050a54(int nSelector);
extern int func_ov002_02050b68(int nSelector);
extern int func_ov002_02050b90(int nSelector);

extern unsigned char data_0204be04;
extern unsigned short data_0204c190;

/* Locked-yaw camera tick: hold the camera at the angle the session dictates,
 * and hand back the ordinary handler as soon as it stops dictating.
 */
void *func_ov002_0204fc54(void)
{
    char *pCam;
    void *pNext;
    int nPlayer;
    VecFx32 *pAnchor;
    int nHandle;
    int nDist;

    pCam = (char *)NNSi_FndGetCurrentRootHeap();
    pNext = 0;
    nPlayer = func_01fffe14();
    pAnchor = func_ov022_020881f8();
    nHandle = func_ov022_02083f5c();

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

    if ((*(unsigned int *)(pCam + 0x38) & 0x4000) == 0) {
        *(int *)(pCam + 0x84) = func_ov002_02050b68(*(int *)(pCam + 0x44));
    }
    *(int *)(pCam + 0x88) = func_ov002_02050a54(*(int *)(pCam + 0x44));

    if ((data_0204c190 & 0x100) != 0 && (data_0204c190 & 0x200) == 0) {
        *(int *)(pCam + 0x50) = func_ov022_02088254(nPlayer);
    }

    if (func_ov002_0204e414(*(int *)(pCam + 0x58), *(int *)(pCam + 0x50)) == 0
        || func_ov022_02086620(nHandle) != 0
        || func_ov022_020886d0(nPlayer) != 0) {
        *(int *)(pCam + 0x40) = 0;
        pNext = (void *)func_ov002_0204d170;
    } else {
        *(int *)(pCam + 0x80) =
            func_ov002_0204e474(*(int *)(pCam + 0x58), *(int *)(pCam + 0x50));
        nDist = func_ov002_02050b90(*(int *)(pCam + 0x44));
        func_ov002_0204eee0((VecFx32 *)(pCam + 0x70), (VecFx32 *)(pCam + 0x64),
                            (int *)(pCam + 0x7c), pAnchor,
                            *(int *)(pCam + 0x80), nDist,
                            *(int *)(pCam + 0x7c));
    }

    func_ov002_0204ff18(func_02023bf0());
    return pNext;
}
