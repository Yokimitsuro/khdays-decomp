/* func_ov017_02080938 -- Ov017_CreateItemClass: allocates the item definition (ov002 object
 * class 0x6c, 0x1c0 bytes per piece), copies the descriptor's model name into +0x58 (emptied
 * first, copied only when the descriptor names one) and its parameter word into +0x68,
 * installs the ten item handlers (message 020804e8, init 020805c4, refresh 020805cc, release
 * 020805c0, start 020805c8, hit 020805d0, node 020806d0, owner 02080708, 02080714 and
 * 0208071c at +0x3c) and stamps kind 0x1d, or 0x1e when the descriptor's flag byte (+0x8) is
 * set.  The item is the piece that hands an item to the player who touches it. */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov017ItemDesc {
    const char *pszModel;     /* 0x00 */
    int   nParam;             /* 0x04 */
    u8    bAlternate;         /* 0x08: kind 0x1e instead of 0x1d */
} Ov017ItemDesc;

typedef struct Ov017ItemDef {
    int nField00;             /* 0x00 */
    int nField04;             /* 0x04 */
    void *pfnMessage;         /* 0x08 */
    void *pfnInit;            /* 0x0c */
    void *pfnRefresh;         /* 0x10 */
    void *pfnRelease;         /* 0x14 */
    void *pfnStart;           /* 0x18 */
    int nField1c;             /* 0x1c */
    void *pfnHit;             /* 0x20 */
    void *pfnGetNode;         /* 0x24 */
    void *pfnGetOwner;        /* 0x28 */
    void *pfnGetA;            /* 0x2c */
    void *pad30;
    void *pad34;
    int nField38;             /* 0x38 */
    void *pfnGetB;            /* 0x3c */
    void *pad40;
    int nField44;             /* 0x44 */
    int nField48;
    u16 nKind;                /* 0x4c */
    char pad4e[0xa];
    char szModel[0x10];       /* 0x58 */
    int  nParam;              /* 0x68 */
} Ov017ItemDef;

extern void *func_ov002_020769b0(int nClass, int nSize, int nOwner);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nLen);
extern void func_ov017_020804e8(void);
extern void func_ov017_020805c4(void);
extern void func_ov017_020805cc(void);
extern void func_ov017_020805c0(void);
extern void func_ov017_020805c8(void);
extern void func_ov017_020805d0(void);
extern void func_ov017_020806d0(void);
extern void func_ov017_02080708(void);
extern void func_ov017_02080714(void);
extern void func_ov017_0208071c(void);

Ov017ItemDef *func_ov017_02080938(int nOwner, Ov017ItemDesc *pDesc)
{
    Ov017ItemDef *pDef;

    pDef = func_ov002_020769b0(0x6c, 7 << 6, nOwner);
    pDef->szModel[0] = 0;
    if (pDesc->pszModel != 0) {
        strncpy(pDef->szModel, pDesc->pszModel, 0x10);
    }
    pDef->nParam = pDesc->nParam;
    pDef->nField00 = 0;
    pDef->nField04 = 0;
    pDef->pfnMessage = (void *)func_ov017_020804e8;
    pDef->pfnInit = (void *)func_ov017_020805c4;
    pDef->pfnRefresh = (void *)func_ov017_020805cc;
    pDef->pfnRelease = (void *)func_ov017_020805c0;
    pDef->pfnStart = (void *)func_ov017_020805c8;
    pDef->nField1c = 0;
    pDef->pfnHit = (void *)func_ov017_020805d0;
    pDef->pfnGetNode = (void *)func_ov017_020806d0;
    pDef->pfnGetOwner = (void *)func_ov017_02080708;
    pDef->pfnGetA = (void *)func_ov017_02080714;
    pDef->nField38 = 0;
    pDef->nField44 = 0;
    pDef->pfnGetB = (void *)func_ov017_0208071c;
    pDef->nKind = pDesc->bAlternate == 0 ? 0x1d : 0x1e;
    return pDef;
}
