/* func_ov023_02083e08 -- Ov023_StepDialog: drive the ov002 dialog opened by Ov023_OpenDialog
 * (02083da0) through its states (+0x875e4).  0: nothing to do, returns 0.  1: counts the timer
 * (+0x10c) down and at 0 moves to 2, darkening the main screen's BG0 a little
 * (G2x_SetBlendBrightness_ on BLDCNT, 1, -8).  2: raises the sub screen's brightness (+0x114)
 * by 4 a frame (BLDCNT_SUB, 0x2c) and at 0 moves to 3.  3: once the ov002 dialog reports done
 * (02067904) it is ended (02023ad0) and forgotten (+0x87588), state 4, and BG0 restored.
 * 4: lowers the brightness by 2 a frame (BLDCNT_SUB, 0xc) and at -16 returns to state 0,
 * sets the global byte 0204bd85 (02020878 1) and returns 0.  While running, the sub engine
 * shows BG1..BG3 (DISPCNT_SUB bits 9..11) and 1 is returned. */
typedef unsigned char  u8;
typedef unsigned int   u32;

static volatile u32 *const REG_DISPCNT_SUB = (volatile u32 *)0x04001000;

typedef struct Ov023Scene {
    u8   pad_00000[0x10c];
    int  nDialogTimer;        /* 0x0010c */
    int  nField110;           /* 0x00110 */
    int  nSubBrightness;      /* 0x00114 */
    u8   pad_00118[0x87588 - 0x118];
    void *pDialog;            /* 0x87588 */
    u8   pad_8758c[0x875e4 - 0x8758c];
    int  nDialogState;        /* 0x875e4 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern void  G2x_SetBlendBrightness_(int nBldCnt, int nPlanes, int nBrightness);
extern int   func_ov002_02067904(void);                             /* the ov002 dialog is done */
extern void  WM_EndKeySharing_0x02023ad0(void *pObject);            /* end an object */
extern void  func_02020878(char bValue);                            /* set the global byte 0204bd85 */
extern Ov023SceneRoot data_ov023_0208a784;

int func_ov023_02083e08(void)
{
    if (data_ov023_0208a784.pScene->nDialogState == 0) {
        return 0;
    }
    switch (data_ov023_0208a784.pScene->nDialogState) {
    case 1:
        data_ov023_0208a784.pScene->nDialogTimer--;
        if (data_ov023_0208a784.pScene->nDialogTimer == 0) {
            data_ov023_0208a784.pScene->nDialogState = 2;
            G2x_SetBlendBrightness_(0x04000050, 1, -8);
        }
        break;
    case 2:
        data_ov023_0208a784.pScene->nSubBrightness += 4;
        G2x_SetBlendBrightness_(0x04001050, 0x2c, data_ov023_0208a784.pScene->nSubBrightness);
        if (data_ov023_0208a784.pScene->nSubBrightness == 0) {
            data_ov023_0208a784.pScene->nDialogState = 3;
        }
        break;
    case 3:
        if (func_ov002_02067904() != 0) {
            WM_EndKeySharing_0x02023ad0(data_ov023_0208a784.pScene->pDialog);
            data_ov023_0208a784.pScene->pDialog = 0;
            data_ov023_0208a784.pScene->nDialogState = 4;
            G2x_SetBlendBrightness_(0x04000050, 1, 0);
        }
        break;
    case 4:
        data_ov023_0208a784.pScene->nSubBrightness -= 2;
        G2x_SetBlendBrightness_(0x04001050, 0xc, data_ov023_0208a784.pScene->nSubBrightness);
        if (data_ov023_0208a784.pScene->nSubBrightness == -16) {
            data_ov023_0208a784.pScene->nDialogState = 0;
            func_02020878(1);
            return 0;
        }
        break;
    }
    *REG_DISPCNT_SUB = (*REG_DISPCNT_SUB & 0xffffe0ff) | 0xe00;
    return 1;
}
