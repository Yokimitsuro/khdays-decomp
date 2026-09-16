/* func_ov015_020820c4 -- Ov015_CreateChestClass: build the class table (0x90 bytes) that
 * owns the 0x744-byte chest pieces from the script's parameter block: the model and
 * sequence names (+0x58 / +0x68), the height (+0x78), the kind byte (+0x7c) and the three
 * fx32 parameters (+0x80 / +0x84 / +0x88); install the chest handlers (message 0208186c,
 * release 020819a0, rebind 02081acc, 02081978, show 020819bc, hit 02081b14, 02081c78,
 * 02081c90, 02081c9c, reset 0208190c) and tag the class 0x1b, or 0x1c when the block's
 * variant byte (+0x1c) is set. */
typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed char    s8;

typedef struct Ov015ChestParams {
    const char *pModel;       /* 0x00 */
    const char *pSequence;    /* 0x04 */
    int  nHeight;             /* 0x08 */
    s8   nKind;               /* 0x0c */
    u8   pad_0d[3];
    int  nParamA;             /* 0x10 */
    int  nParamB;             /* 0x14 */
    int  nParamC;             /* 0x18 */
    u8   bVariant;            /* 0x1c */
    u8   pad_1d[3];
} Ov015ChestParams;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);
extern void func_ov015_0208186c(void);
extern void func_ov015_020819a0(void);
extern void func_ov015_02081acc(void);
extern void func_ov015_02081978(void);
extern void func_ov015_020819bc(void);
extern void func_ov015_02081b14(void);
extern void func_ov015_02081c78(void);
extern void func_ov015_02081c90(void);
extern void func_ov015_02081c9c(void);
extern void func_ov015_0208190c(void);

void *func_ov015_020820c4(void *pCtx, const Ov015ChestParams *pParams)
{
    char *pTable;
    u16 nClass;

    pTable = (char *)func_ov002_020769b0(0x90, 0x744, pCtx);
    strncpy(pTable + 0x58, pParams->pModel, 0x10);
    strncpy(pTable + 0x68, pParams->pSequence, 0x10);
    *(int *)(pTable + 0x78) = pParams->nHeight;
    *(s8 *)(pTable + 0x7c) = pParams->nKind;
    *(int *)(pTable + 0x80) = pParams->nParamA;
    *(int *)(pTable + 0x84) = pParams->nParamB;
    *(int *)(pTable + 0x88) = pParams->nParamC;
    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = (int)func_ov015_0208186c;
    *(int *)(pTable + 0x0c) = (int)func_ov015_020819a0;
    *(int *)(pTable + 0x10) = (int)func_ov015_02081acc;
    *(int *)(pTable + 0x14) = (int)func_ov015_02081978;
    *(int *)(pTable + 0x18) = (int)func_ov015_020819bc;
    *(int *)(pTable + 0x1c) = (int)func_ov015_02081b14;
    *(int *)(pTable + 0x20) = 0;
    *(int *)(pTable + 0x24) = (int)func_ov015_02081c78;
    *(int *)(pTable + 0x28) = (int)func_ov015_02081c90;
    *(int *)(pTable + 0x2c) = (int)func_ov015_02081c9c;
    *(int *)(pTable + 0x38) = (int)func_ov015_0208190c;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x3c) = 0;
    if (pParams->bVariant == 0) {
        nClass = 0x1b;
    } else {
        nClass = 0x1c;
    }
    *(u16 *)(pTable + 0x4c) = nClass;
    return pTable;
}
