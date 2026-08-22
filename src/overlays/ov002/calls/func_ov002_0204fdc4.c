typedef struct {
    int x, y, z;
} VecFx32;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_01fffe14(void);
extern void *func_02023bf0(void);   /* the active scene */

extern VecFx32 *func_ov022_020881f8(int nPlayer);
extern int func_ov022_02083f5c(void);
extern int func_ov022_020881d8(void);
extern int func_ov022_02088338(void);

extern void func_ov002_0204eee0(VecFx32 *pOutFocus, VecFx32 *pOutCamera,
                                int *pOutDist, VecFx32 *pAnchor, int nAngle,
                                int nDist, int nPrevDist);
extern void func_ov002_0204ff18(void *pScene);
extern int func_ov002_02050a54(int nSelector);
extern int func_ov002_02050b68(int nSelector);

extern unsigned char data_0204be04;
extern short data_0203d210[];   /* angle sin/cos table, 4 bytes per entry */

/* Reset the camera to its default pose and publish it in one go.
 */
void *func_ov002_0204fdc4(void)
{
    char *pCam;
    int nPlayer;
    VecFx32 *pAnchor;

    pCam = (char *)NNSi_FndGetCurrentRootHeap();
    nPlayer = func_01fffe14();
    pAnchor = func_ov022_020881f8(nPlayer);
    func_ov022_02083f5c();

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

    *(unsigned int *)(pCam + 0x38) &= 0xfffcdfff;
    *(int *)(pCam + 0x60) = func_ov002_02050a54(0);
    *(int *)(pCam + 0x5c) = func_ov002_02050b68(0);
    *(unsigned short *)(pCam + 0xa0) = 0x1555;
    *(unsigned short *)(pCam + 0xa2) = 0x1555;
    *(int *)pCam =
        data_0203d210[(*(unsigned short *)(pCam + 0xa0) >> 4) * 2];
    *(int *)(pCam + 4) =
        data_0203d210[(*(unsigned short *)(pCam + 0xa2) >> 4) * 2 + 1];

    func_ov002_0204eee0((VecFx32 *)(pCam + 0x70), (VecFx32 *)(pCam + 0x64),
                        (int *)(pCam + 0x7c), pAnchor,
                        *(int *)(pCam + 0x58), 0x3000, 0x3000);

    *(VecFx32 *)(pCam + 0x20) = *(VecFx32 *)(pCam + 0x64);
    *(VecFx32 *)(pCam + 0x14) = *(VecFx32 *)(pCam + 0x70);
    *(int *)(pCam + 0x54) = *(int *)(pCam + 0x7c);
    *(int *)(pCam + 0x9c) = 1;
    *(int *)(pCam + 0xb4) = 0x1f;

    func_ov002_0204ff18(func_02023bf0());
    return 0;
}
