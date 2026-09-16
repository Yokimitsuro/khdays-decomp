/* func_ov016_02080780 -- Ov016_CreateFollowerClass: allocate the class-0x16 definition (class
 * 0x68 of the ov002 object allocator, 0x1cc bytes), copy the descriptor's name into the
 * 0x10-byte field at +0x58 when there is one (the field is emptied first), install the nine
 * handlers of the follower (the object that trails a player) and stamp kind 0x16.
 *
 * Sibling of Ov016_CreateEntry (0207feb8, class 0x13) and Ov016_CreateEntryClass80 (02081f64);
 * the size is written 0x73 * 4 because that is how the ROM materialises it. */
typedef unsigned short u16;

typedef struct Ov016FollowerDesc {
    char *pszName;            /* 0x00 */
} Ov016FollowerDesc;

typedef struct Ov016FollowerDef {
    int nField00;             /* 0x00 */
    int nField04;             /* 0x04 */
    int nField08;             /* 0x08 */
    void *pfnInit;            /* 0x0c */
    void *pfnSubmit;          /* 0x10 */
    void *pfnRelease;         /* 0x14 */
    void *pfnStart;           /* 0x18 */
    int nField1c;             /* 0x1c */
    int nField20;             /* 0x20 */
    int nField24;             /* 0x24 */
    void *pad28;
    void *pfnQuery;           /* 0x2c */
    void *pfnMoveTo;          /* 0x30 */
    void *pfnGetB;            /* 0x34 */
    int nField38;             /* 0x38 */
    void *pfnStep;            /* 0x3c */
    void *pfnGetA;            /* 0x40 */
    int nField44;             /* 0x44 */
    int nField48;
    u16 nKind;                /* 0x4c */
    char pad4e[0xa];
    char szName[0x10];        /* 0x58 */
} Ov016FollowerDef;

extern void *func_ov002_020769b0(int nClass, int nSize, int nOwner);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nLen);
extern void func_ov016_02080024(void);
extern void func_ov016_020800fc(void);
extern void func_ov016_02080014(void);
extern void func_ov016_02080030(void);
extern void func_ov016_02080124(void);
extern void func_ov016_0208012c(void);
extern void func_ov016_02080198(void);
extern void func_ov016_02080190(void);
extern void func_ov016_0208076c(void);

Ov016FollowerDef *func_ov016_02080780(int nOwner, Ov016FollowerDesc *pDesc)
{
    Ov016FollowerDef *pDef;

    pDef = func_ov002_020769b0(0x68, 0x73 * 4, nOwner);
    pDef->szName[0] = 0;
    if (pDesc->pszName != 0) {
        strncpy(pDef->szName, pDesc->pszName, 0x10);
    }
    pDef->nField00 = 0;
    pDef->nField04 = 0;
    pDef->nField08 = 0;
    pDef->pfnInit = (void *)func_ov016_02080024;
    pDef->pfnSubmit = (void *)func_ov016_020800fc;
    pDef->pfnRelease = (void *)func_ov016_02080014;
    pDef->pfnStart = (void *)func_ov016_02080030;
    pDef->nField1c = 0;
    pDef->nField20 = 0;
    pDef->nField24 = 0;
    pDef->pfnQuery = (void *)func_ov016_02080124;
    pDef->pfnMoveTo = (void *)func_ov016_0208012c;
    pDef->pfnGetB = (void *)func_ov016_02080198;
    pDef->nField38 = 0;
    pDef->pfnGetA = (void *)func_ov016_02080190;
    pDef->nField44 = 0;
    pDef->pfnStep = (void *)func_ov016_0208076c;
    pDef->nKind = 0x16;
    return pDef;
}
