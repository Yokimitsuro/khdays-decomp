/* func_ov016_020825b4 -- Ov016_CreateHazardClass: allocate the kind-1 definition (ov002 object
 * class 0x74, 0x2c0 bytes), copy the descriptor's model name into +0x58, carry its four shorts
 * (+0x68, +0x6a, +0x6c and the sequence at +0x6e, stored out of order), the target flags
 * (+0x70) and the target slot / index bytes (+0x72 / +0x73) across, install the six hazard
 * handlers (init 02082294, release 020822cc, rebind 02082380, 020822c0, start 020822e0,
 * 020823a8) and stamp kind 1.  The hazard is the modelled object that delivers hits to the
 * pieces of the target slot (Ov016_HazardStep 02082444). */
typedef signed char    s8;
typedef unsigned short u16;

typedef struct Ov016HazardDesc {
    char *pszModel;           /* 0x00 */
    short nParamA;            /* 0x04 */
    short nParamB;            /* 0x06 */
    short nParamC;            /* 0x08 */
    short nSequence;          /* 0x0a */
    u16   nTargetFlags;       /* 0x0c */
    s8    nTargetSlot;        /* 0x0e */
    s8    nTargetIndex;       /* 0x0f */
} Ov016HazardDesc;

typedef struct Ov016HazardDef {
    int nField00;             /* 0x00 */
    int nField04;             /* 0x04 */
    void *pfnInit;            /* 0x08 */
    void *pfnRelease;         /* 0x0c */
    void *pfnRebind;          /* 0x10 */
    void *pfnRefresh;         /* 0x14 */
    void *pfnStart;           /* 0x18 */
    int nField1c;             /* 0x1c */
    int nField20;             /* 0x20 */
    int nField24;             /* 0x24 */
    void *pad28;
    void *pfnGetNode;         /* 0x2c */
    void *pad30;
    void *pad34;
    int nField38;             /* 0x38 */
    int nField3c;             /* 0x3c */
    void *pad40;
    int nField44;             /* 0x44 */
    int nField48;
    u16 nKind;                /* 0x4c */
    char pad4e[0xa];
    char szModel[0x10];       /* 0x58 */
    short nParamA;            /* 0x68 */
    short nParamB;            /* 0x6a */
    short nParamC;            /* 0x6c */
    short nSequence;          /* 0x6e */
    u16   nTargetFlags;       /* 0x70 */
    s8    nTargetSlot;        /* 0x72 */
    s8    nTargetIndex;       /* 0x73 */
} Ov016HazardDef;

extern void *func_ov002_020769b0(int nClass, int nSize, int nOwner);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nLen);
extern void func_ov016_02082294(void);
extern void func_ov016_020822cc(void);
extern void func_ov016_02082380(void);
extern void func_ov016_020822c0(void);
extern void func_ov016_020822e0(void);
extern void func_ov016_020823a8(void);

Ov016HazardDef *func_ov016_020825b4(int nOwner, Ov016HazardDesc *pDesc)
{
    Ov016HazardDef *pDef;

    pDef = func_ov002_020769b0(0x74, 0xb << 6, nOwner);
    strncpy(pDef->szModel, pDesc->pszModel, 0x10);
    pDef->nSequence = pDesc->nSequence;
    pDef->nParamA = pDesc->nParamA;
    pDef->nParamB = pDesc->nParamB;
    pDef->nParamC = pDesc->nParamC;
    pDef->nTargetFlags = pDesc->nTargetFlags;
    pDef->nTargetSlot = pDesc->nTargetSlot;
    pDef->nTargetIndex = pDesc->nTargetIndex;
    pDef->nField00 = 0;
    pDef->nField04 = 0;
    pDef->pfnInit = (void *)func_ov016_02082294;
    pDef->pfnRelease = (void *)func_ov016_020822cc;
    pDef->pfnRebind = (void *)func_ov016_02082380;
    pDef->pfnRefresh = (void *)func_ov016_020822c0;
    pDef->pfnStart = (void *)func_ov016_020822e0;
    pDef->nField1c = 0;
    pDef->nField20 = 0;
    pDef->nField24 = 0;
    pDef->pfnGetNode = (void *)func_ov016_020823a8;
    pDef->nField38 = 0;
    pDef->nField44 = 0;
    pDef->nField3c = 0;
    pDef->nKind = 1;
    return pDef;
}
