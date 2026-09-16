/* func_ov023_02082d20 -- Ov023_SceneInit: constructor of the event scene's main object.  Takes
 * the current context as the scene object (NNSi_FndGetCurrentRootHeap, kept in
 * data_ov023_0208a784[1]) and clears its 0x875ec bytes; registers the message table
 * (data_ov023_0208a384, slot 1) and the script-command table (data_ov023_0208a66c, slot 0x14)
 * with the global tables (02020aa8); formats the request into the scene's name (+0x87598,
 * OS_SPrintf) and keeps the request's word at +0x44 (+0x875e0).  In global mode 4 the
 * background layers are prepared (Ov023_LoadBackgrounds 02083100, 02083270) and, in a
 * session (02030670), the sign-in panel at +0x12c set up (020832e4); mode 0xc only loads the
 * backgrounds.  The two words at +0x875e4 are cleared, the fade level (0201e428) becomes the
 * end value of both fade tweens (+0x104, 0x14 bytes each) whose elapsed counter and duration
 * are cleared.  When bit 3 of the global mode halfword (02020a9c) is set the 3D camera block
 * at +0x87554 is initialised (0202e8ec / 0202ea14 with the mode word +0x87594 = 0xb /
 * 0202ea1c), the "dual3d_update" task registered on Ov023_Dual3DUpdate (02083784, priority
 * 1, 02000f48), the OBJ matrices reset (02011134 on a 10-word identity block, banks 0x20 /
 * 0x40, 0201133c, 02011174 0x4000 / 1).  Session bits 1 / 2 (data_0204c240) also bring up
 * the sprite objects (02083920).  Finally status bit 1 (+0x8758c) is raised, the dialogue
 * tween (+0x87564) cleared (02035f84) and the poll state Ov023_ScenePoll (02082ec0) returned. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov023SceneRequest {
    char szName[0x44];        /* 0x00 */
    int  nParam44;            /* 0x44 */
} Ov023SceneRequest;

typedef struct Ov023Tween {
    int  nStart;              /* 0x00 */
    int  nTarget;             /* 0x04 */
    int  nElapsed;            /* 0x08 */
    int  nDuration;           /* 0x0c */
    int  nValue;              /* 0x10 */
} Ov023Tween;

typedef struct Ov023Scene {
    u8   pad_00000[0x104];
    Ov023Tween aFade[2];      /* 0x00104 */
    u8   panel[0x87554 - 0x12c]; /* 0x0012c: the sign-in panel */
    u8   camera[0x87564 - 0x87554]; /* 0x87554: the 3D camera block */
    u8   dialogue[0x8758c - 0x87564]; /* 0x87564: the dialogue tween */
    u16  nStatus;             /* 0x8758c */
    u8   pad_8758e[6];
    int  nCameraMode;         /* 0x87594 */
    char szName[0x875e0 - 0x87598]; /* 0x87598 */
    int  nParam;              /* 0x875e0 */
    int  nWord875e4;          /* 0x875e4 */
    int  nWord875e8;          /* 0x875e8 */
} Ov023Scene;

typedef struct Ov023SceneRoot {
    int  nField00;            /* 0x00 */
    Ov023Scene *pScene;       /* 0x04 */
} Ov023SceneRoot;

extern Ov023Scene *NNSi_FndGetCurrentRootHeap(void);
extern void  MI_CpuFill8(void *pDst, int nValue, unsigned int nSize);
extern void  func_02020aa8(int nSlot, const void *pTable);          /* register a global table */
extern void  OS_SPrintf(char *pBuffer, const char *pFormat);
extern int   func_02020a9c(void);                                   /* the global mode halfword */
extern void  func_ov023_02083100(void);                             /* Ov023_LoadBackgrounds */
extern void  func_ov023_02083270(void);
extern int   func_02030670(void);                                   /* Session_IsActive */
extern void  func_ov023_020832e4(void *pPanel);                     /* set the sign-in panel up */
extern int   func_0201e428(void);                                   /* the main fade level */
extern void  func_0202e8ec(void *pCamera, int nArg);
extern void  func_0202ea14(void *pCamera, int nMode);
extern void  func_0202ea1c(void *pCamera, int nArg);
extern void  func_02000f48(int nPriority, const char *pName, void (*pfn)(void)); /* register a named task */
extern void  func_02011134(void *pMatrices);
extern void  GX_BeginLoadOBJExtPltt(int nOffset);
extern void  GX_SetBankForOBJ(int nBank);
extern void  func_0201133c(void);
extern void  func_02011174(int nA, int nB);
extern void  func_ov023_02083920(void);                             /* bring the sprite objects up */
extern void  func_02035f84(void *pTween);                           /* Tween_Clear */
extern void  func_ov023_02083784(void);                             /* Ov023_Dual3DUpdate */
extern int   func_ov023_02082ec0(void);                             /* Ov023_ScenePoll */
extern Ov023SceneRoot data_ov023_0208a784;
extern void *data_ov023_0208a384[];                                 /* the message table */
extern void *data_ov023_0208a66c[];                                 /* the script-command table */
extern char  data_ov023_0208a04c[];                                 /* "dual3d_update" */
extern u8    data_0204c240;                                         /* session bits */

void *func_ov023_02082d20(Ov023SceneRequest *pRequest)
{
    int aMatrix[10];
    int i;

    data_ov023_0208a784.pScene = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov023_0208a784.pScene, 0, sizeof(Ov023Scene));
    func_02020aa8(1, data_ov023_0208a384);
    func_02020aa8(0x14, data_ov023_0208a66c);
    OS_SPrintf(data_ov023_0208a784.pScene->szName, pRequest->szName);
    data_ov023_0208a784.pScene->nParam = pRequest->nParam44;
    switch (func_02020a9c()) {
    case 0xc:
        func_ov023_02083100();
        break;
    case 4:
        func_ov023_02083100();
        func_ov023_02083270();
        if (func_02030670() != 0) {
            func_ov023_020832e4(data_ov023_0208a784.pScene->panel);
        }
        break;
    }
    data_ov023_0208a784.pScene->nWord875e4 = 0;
    data_ov023_0208a784.pScene->nWord875e8 = 0;
    data_ov023_0208a784.pScene->aFade[1].nValue = func_0201e428();
    data_ov023_0208a784.pScene->aFade[0].nValue = data_ov023_0208a784.pScene->aFade[1].nValue;
    for (i = 0; i < 2; i++) {
        data_ov023_0208a784.pScene->aFade[i].nElapsed = 0;
        data_ov023_0208a784.pScene->aFade[i].nDuration = 0;
    }
    if (func_02020a9c() & 8) {
        data_ov023_0208a784.pScene->nCameraMode = 0xb;
        func_0202e8ec(data_ov023_0208a784.pScene->camera, 1);
        func_0202ea14(data_ov023_0208a784.pScene->camera, data_ov023_0208a784.pScene->nCameraMode);
        func_0202ea1c(data_ov023_0208a784.pScene->camera, 0);
        func_02000f48(1, data_ov023_0208a04c, func_ov023_02083784);
        aMatrix[0] = 0;
        aMatrix[1] = 0x20000;
        aMatrix[2] = 0;
        aMatrix[3] = 0x20000;
        aMatrix[4] = 0;
        aMatrix[5] = 0;
        aMatrix[6] = 0;
        aMatrix[7] = 0x20000;
        aMatrix[8] = 0;
        aMatrix[9] = 0x20000;
        func_02011134(aMatrix);
        GX_BeginLoadOBJExtPltt(0x20);
        GX_SetBankForOBJ(0x40);
        func_0201133c();
        func_02011174(0x4000, 1);
    }
    if ((data_0204c240 & 4) || (data_0204c240 & 2)) {
        func_ov023_02083920();
    }
    data_ov023_0208a784.pScene->nStatus |= 2;
    func_02035f84(data_ov023_0208a784.pScene->dialogue);
    return func_ov023_02082ec0;
}
