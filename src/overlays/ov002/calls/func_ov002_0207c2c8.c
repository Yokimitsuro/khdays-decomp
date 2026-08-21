typedef unsigned short u16;

/* The descriptor the caller fills in for one travelling-element class. */
typedef struct {
    const char *pName;              /* +0x00 */
    int nOwnerArg;                  /* +0x04 */
    signed char bKind;              /* +0x08 */
    short nParamA;                  /* +0x0a */
    short nParamB;                  /* +0x0c */
    short nParamC;                  /* +0x0e */
    short nEffectId;                /* +0x10 */
    short nEffectMode;              /* +0x12 */
    signed char bReturnKind;        /* +0x14 */
    short nSpeed;                   /* +0x16 */
    short nHitDist;                 /* +0x18 */
    signed char bRelease;           /* +0x1a */
} Ov002TravelClassDesc;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);

extern void func_ov002_0207be9c(void);
extern void func_ov002_0207bf24(void);
extern void func_ov002_0207bfc8(void);
extern void func_ov002_0207befc(void);
extern void func_ov002_0207bf30(void);
extern void func_ov002_0207c020(void);
extern void func_ov002_0207c090(void);
extern void func_ov002_0207c098(void);
extern void func_ov002_0207c0a4(void);

/* Create the table that owns one class of travelling element.
 *
 * Allocates the 0x80 byte table together with room for 0x2c8 byte elements,
 * blanks the name and copies the descriptor's one over it when there is one,
 * carries the class's parameters across and installs its nine handlers.
 */
void *func_ov002_0207c2c8(void *pCtx, const Ov002TravelClassDesc *pDesc)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x80, 0x2c8, pCtx);

    *(char *)(pTable + 0x58) = 0;
    if (pDesc->pName != 0) {
        strncpy(pTable + 0x58, pDesc->pName, 0x10);
    }

    *(int *)(pTable + 0x68) = pDesc->nOwnerArg;
    *(signed char *)(pTable + 0x6c) = pDesc->bKind;
    *(short *)(pTable + 0x6e) = pDesc->nParamA;
    *(short *)(pTable + 0x70) = pDesc->nParamB;
    *(short *)(pTable + 0x72) = pDesc->nParamC;
    *(short *)(pTable + 0x7a) = pDesc->nSpeed;
    *(signed char *)(pTable + 0x78) = pDesc->bReturnKind;
    *(short *)(pTable + 0x74) = pDesc->nEffectId;
    *(short *)(pTable + 0x76) = pDesc->nEffectMode;
    *(short *)(pTable + 0x7c) = pDesc->nHitDist;
    *(signed char *)(pTable + 0x7e) = pDesc->bRelease;

    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = (int)func_ov002_0207be9c;
    *(int *)(pTable + 0x0c) = (int)func_ov002_0207bf24;
    *(int *)(pTable + 0x10) = (int)func_ov002_0207bfc8;
    *(int *)(pTable + 0x14) = (int)func_ov002_0207befc;
    *(int *)(pTable + 0x18) = (int)func_ov002_0207bf30;
    *(int *)(pTable + 0x1c) = 0;
    *(int *)(pTable + 0x20) = (int)func_ov002_0207c020;
    *(int *)(pTable + 0x24) = (int)func_ov002_0207c090;
    *(int *)(pTable + 0x28) = (int)func_ov002_0207c098;
    *(int *)(pTable + 0x2c) = (int)func_ov002_0207c0a4;

    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x3c) = 0;

    *(u16 *)(pTable + 0x4c) = 0x21;

    return pTable;
}
