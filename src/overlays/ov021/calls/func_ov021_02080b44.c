/* func_ov021_02080b44 -- Ov021_CreateEmblemClass: allocates the class-0x1f definition (ov002
 * object class 0x78, 0x2c0 bytes per piece) and keeps it in the overlay's class slot
 * (data_ov021_02080f40, the one Ov021_EmblemResetOthers walks); copies the descriptor's
 * sequence name into +0x58 and its model name into +0x68 (each field emptied first), installs
 * the five emblem handlers (message 02080540, init 02080650, refresh 02080738, release
 * 02080600, start 02080660), clears the other slots and stamps kind 0x1f.  The emblem is the
 * mission-mode collectable that shrinks as its timer runs out and, once a player reaches it,
 * spirals into that player. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov021EmblemDesc {
    const char *pszSequence;  /* 0x00 */
    const char *pszModel;     /* 0x04 */
} Ov021EmblemDesc;

typedef struct Ov021EmblemDef {
    int nField00;             /* 0x00 */
    int nField04;             /* 0x04 */
    void *pfnMessage;         /* 0x08 */
    void *pfnInit;            /* 0x0c */
    void *pfnRefresh;         /* 0x10 */
    void *pfnRelease;         /* 0x14 */
    void *pfnStart;           /* 0x18 */
    int nField1c;             /* 0x1c */
    int nField20;             /* 0x20 */
    int nField24;             /* 0x24 */
    int nField28;             /* 0x28 */
    int nField2c;             /* 0x2c */
    void *pad30;
    void *pad34;
    int nField38;             /* 0x38 */
    int nField3c;             /* 0x3c */
    void *pad40;
    int nField44;             /* 0x44 */
    int nField48;
    u16 nKind;                /* 0x4c */
    char pad4e[0xa];
    char szSequence[0x10];    /* 0x58 */
    char szModel[0x10];       /* 0x68 */
} Ov021EmblemDef;

extern void *func_ov002_020769b0(int nClass, int nSize, int nCount);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nLen);
extern void func_ov021_02080540(void);
extern void func_ov021_02080650(void);
extern void func_ov021_02080738(void);
extern void func_ov021_02080600(void);
extern void func_ov021_02080660(void);
extern Ov021EmblemDef *data_ov021_02080f40;                          /* the emblem class of the mission */

Ov021EmblemDef *func_ov021_02080b44(int nCount, Ov021EmblemDesc *pDesc)
{
    Ov021EmblemDef *pDef;

    pDef = func_ov002_020769b0(0x78, 0xb << 6, nCount);
    data_ov021_02080f40 = pDef;
    pDef->szSequence[0] = 0;
    strncpy(pDef->szSequence, pDesc->pszSequence, 0x10);
    pDef->szModel[0] = 0;
    strncpy(pDef->szModel, pDesc->pszModel, 0x10);
    pDef->nField00 = 0;
    pDef->nField04 = 0;
    pDef->pfnMessage = (void *)func_ov021_02080540;
    pDef->pfnInit = (void *)func_ov021_02080650;
    pDef->pfnRefresh = (void *)func_ov021_02080738;
    pDef->pfnRelease = (void *)func_ov021_02080600;
    pDef->pfnStart = (void *)func_ov021_02080660;
    pDef->nField1c = 0;
    pDef->nField20 = 0;
    pDef->nField24 = 0;
    pDef->nField28 = 0;
    pDef->nField2c = 0;
    pDef->nField38 = 0;
    pDef->nField44 = 0;
    pDef->nField3c = 0;
    pDef->nKind = 0x1f;
    return pDef;
}
