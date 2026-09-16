/* func_ov021_0208024c -- Ov021_CreatePrizeBoxClass: allocates the class-0x11 definition (ov002
 * object class 0x158, 0x1c0 bytes per piece, one piece per prize), copies the descriptor's
 * model name into +0x58 (emptied first, copied only when the descriptor names one), its
 * parameter word (+0x68), node kind (+0x6c), three placement shorts (+0x6e..+0x72), halfword
 * (+0x74) and byte (+0x76); on the host it builds the prize order (+0x138: 0..n-1, then 32
 * random swaps, Rand16NextScaled 02023e80) so each box of the class gets a different prize;
 * copies the descriptor's six-byte prizes into +0x78 (MI_CpuCopy8) and installs the ten
 * prize-box handlers (message 0207faf8, init 0207fbb8, refresh 0207fca0, release 0207fb80,
 * start 0207fbc8, hit 0207fd98, node 0207fec0, owner 0207fed4, 0207fee0, 0207fee8 at +0x3c)
 * and stamps kind 0x11.  The prize box is ov021's box holding one prize of a shuffled list. */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov021Prize {
    char  nType;              /* 0x00: 0 item, 1 munny, 2 keyed object, 3 nothing */
    u8    pad_01;
    short nValue;             /* 0x02 */
    u8    bFlag;              /* 0x04 */
    u8    pad_05;
} Ov021Prize;

typedef struct Ov021PrizeBoxDesc {
    const char *pszModel;     /* 0x00 */
    int   nParam;             /* 0x04 */
    s8    nNodeKind;          /* 0x08 */
    u8    pad_09;
    short nPlaceA;            /* 0x0a */
    short nPlaceB;            /* 0x0c */
    short nPlaceC;            /* 0x0e */
    u16   nHalf10;            /* 0x10 */
    u8    nByte12;            /* 0x12 */
    u8    pad_13;
    Ov021Prize aPrize[1];     /* 0x14: one per box */
} Ov021PrizeBoxDesc;

typedef struct Ov021PrizeBoxDef {
    int nField00;             /* 0x00 */
    int nField04;             /* 0x04 */
    void *pfnMessage;         /* 0x08 */
    void *pfnInit;            /* 0x0c */
    void *pfnRefresh;         /* 0x10 */
    void *pfnRelease;         /* 0x14 */
    void *pfnStart;           /* 0x18 */
    void *pfnHit;             /* 0x1c */
    int nField20;             /* 0x20 */
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
    s8   nNodeKind;           /* 0x6c */
    u8   pad_6d;
    short nPlaceA;            /* 0x6e */
    short nPlaceB;            /* 0x70 */
    short nPlaceC;            /* 0x72 */
    u16  nHalf74;             /* 0x74 */
    u8   nByte76;             /* 0x76 */
    u8   pad_77;
    Ov021Prize aPrize[0x20];  /* 0x78 */
    s8   aOrder[0x20];        /* 0x138: which prize each box gets */
} Ov021PrizeBoxDef;

extern void *func_ov002_020769b0(int nClass, int nSize, int nCount);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nLen);
extern int   func_02030788(void);                                     /* Session_GetLocalPlayerIndex */
extern int   func_02023e80(int nRange);                               /* Rand16NextScaled */
extern void  MI_CpuCopy8(const void *pSrc, void *pDst, unsigned int nSize);
extern void func_ov021_0207faf8(void);
extern void func_ov021_0207fbb8(void);
extern void func_ov021_0207fca0(void);
extern void func_ov021_0207fb80(void);
extern void func_ov021_0207fbc8(void);
extern void func_ov021_0207fd98(void);
extern void func_ov021_0207fec0(void);
extern void func_ov021_0207fed4(void);
extern void func_ov021_0207fee0(void);
extern void func_ov021_0207fee8(void);

Ov021PrizeBoxDef *func_ov021_0208024c(int nCount, Ov021PrizeBoxDesc *pDesc)
{
    Ov021PrizeBoxDef *pDef;
    int i;
    int j;
    int nA;
    int nB;
    s8 nSwap;

    pDef = func_ov002_020769b0(0x158, 0x1c0, nCount);
    pDef->szModel[0] = 0;
    if (pDesc->pszModel != 0) {
        strncpy(pDef->szModel, pDesc->pszModel, 0x10);
    }
    pDef->nParam = pDesc->nParam;
    pDef->nNodeKind = pDesc->nNodeKind;
    pDef->nPlaceA = pDesc->nPlaceA;
    pDef->nPlaceB = pDesc->nPlaceB;
    pDef->nPlaceC = pDesc->nPlaceC;
    pDef->nHalf74 = pDesc->nHalf10;
    pDef->nByte76 = pDesc->nByte12;
    if (func_02030788() == 0) {
        for (i = 0; i < nCount; i++) {
            pDef->aOrder[i] = i;
        }
        for (i = 0; i < 0x20; i++) {
            nA = func_02023e80(nCount);
            nB = func_02023e80(nCount);
            nSwap = pDef->aOrder[nA];
            pDef->aOrder[nA] = pDef->aOrder[nB];
            pDef->aOrder[nB] = nSwap;
        }
    }
    for (j = 0; j < nCount; j++) {
        MI_CpuCopy8(&pDesc->aPrize[j], &pDef->aPrize[j], 6);
    }
    pDef->nField00 = 0;
    pDef->nField04 = 0;
    pDef->pfnMessage = (void *)func_ov021_0207faf8;
    pDef->pfnInit = (void *)func_ov021_0207fbb8;
    pDef->pfnRefresh = (void *)func_ov021_0207fca0;
    pDef->pfnRelease = (void *)func_ov021_0207fb80;
    pDef->pfnStart = (void *)func_ov021_0207fbc8;
    pDef->pfnHit = (void *)func_ov021_0207fd98;
    pDef->nField20 = 0;
    pDef->pfnGetNode = (void *)func_ov021_0207fec0;
    pDef->pfnGetOwner = (void *)func_ov021_0207fed4;
    pDef->pfnGetA = (void *)func_ov021_0207fee0;
    pDef->nField38 = 0;
    pDef->nField44 = 0;
    pDef->pfnGetB = (void *)func_ov021_0207fee8;
    pDef->nKind = 0x11;
    return pDef;
}
