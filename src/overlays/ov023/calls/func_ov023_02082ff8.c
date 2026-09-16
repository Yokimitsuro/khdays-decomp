/* func_ov023_02082ff8 -- Ov023_SceneDestroy: destructor of the event scene's main object.
 * Sets the blend registers to a flat 0xff / 0xc0 and hides the sub engine's windows (DISPCNT_SUB
 * bits 13..15), resets the actor table (Ov023_ResetActors 02083bd4) and the entity manager
 * (0202b788 / 0202b73c); in a session (bits 1 / 2 of data_0204c240) the sign-in panel's
 * display (+0x144) is released (02032428); in a session in a mode other than 0xc the
 * scene's two heap blocks (+0x130 and +0x12c) are freed (NNSi_FndFreeFromDefaultHeap); the two
 * event text containers (+0x1db4c, +0x1db50) are closed (02024fd4) and the sub-object at
 * +0x87580 ended (02023ad0) when present; the message and script-command tables are
 * unregistered (02020aa8 slots 1 / 0x14) and the scene pointer (data_ov023_0208a784[1])
 * cleared. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

static volatile u16 *const REG_BLDCNT = (volatile u16 *)0x04000040;
static volatile u16 *const REG_BLDY = (volatile u16 *)0x04000044;
static volatile u32 *const REG_DISPCNT_SUB = (volatile u32 *)0x04001000;

typedef struct Ov023Scene {
    u8   pad_00000[0x12c];
    void *pBlock12c;          /* 0x0012c */
    void *pBlock130;          /* 0x00130 */
    u8   pad_00134[0x144 - 0x134];
    u8   display[0x1db4c - 0x144]; /* 0x00144 */
    void *pSharedText;        /* 0x1db4c */
    void *pWorldText;         /* 0x1db50 */
    u8   pad_1db54[0x87580 - 0x1db54];
    void *pSubObject;         /* 0x87580 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern void func_ov023_02083bd4(void);                              /* Ov023_ResetActors */
extern void func_0202b788(void);                                    /* EntityManager_ReleaseViews */
extern void func_0202b73c(void);                                    /* EntityManager_ResetSingleton */
extern void func_02032428(void *pDisplay);                          /* release a display */
extern int  func_02030670(void);                                    /* Session_IsActive */
extern int  func_02020a9c(void);                                    /* the global mode halfword */
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_02024fd4(void *pContainer);                        /* close a text container */
extern void WM_EndKeySharing_0x02023ad0(void *pObject);            /* end a sub-object */
extern void func_02020aa8(int nSlot, const void *pTable);          /* register a global table */
extern u8   data_0204c240;                                          /* session bits */
extern Ov023SceneRoot data_ov023_0208a784;

void func_ov023_02082ff8(void)
{
    *REG_BLDCNT = 0xff;
    *REG_BLDY = 0xc0;
    *REG_DISPCNT_SUB &= 0xffff1fff;
    func_ov023_02083bd4();
    func_0202b788();
    func_0202b73c();
    if ((data_0204c240 & 4) || (data_0204c240 & 2)) {
        func_02032428(data_ov023_0208a784.pScene->display);
    }
    if (func_02030670() != 0 && func_02020a9c() != 0xc) {
        NNSi_FndFreeFromDefaultHeap(data_ov023_0208a784.pScene->pBlock130);
        NNSi_FndFreeFromDefaultHeap(data_ov023_0208a784.pScene->pBlock12c);
    }
    if (data_ov023_0208a784.pScene->pSharedText != 0) {
        func_02024fd4(data_ov023_0208a784.pScene->pSharedText);
    }
    if (data_ov023_0208a784.pScene->pWorldText != 0) {
        func_02024fd4(data_ov023_0208a784.pScene->pWorldText);
    }
    if (data_ov023_0208a784.pScene->pSubObject != 0) {
        WM_EndKeySharing_0x02023ad0(data_ov023_0208a784.pScene->pSubObject);
    }
    func_02020aa8(1, 0);
    func_02020aa8(0x14, 0);
    data_ov023_0208a784.pScene = 0;
}
