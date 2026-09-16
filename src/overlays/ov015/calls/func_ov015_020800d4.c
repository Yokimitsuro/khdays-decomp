/* func_ov015_020800d4 -- Ov015_CreatePickupClass: build the class table (0x8c bytes) that
 * owns the 0x154-byte pickup pieces from the script's parameter block: the model name (+0x58,
 * left empty when the block has none) and sequence name (+0x68), the height (+0x78), the
 * three shorts (+0x7c / +0x7e / +0x80), the two bytes (+0x82 / +0x83), the kind (+0x84) and
 * the parameter word (+0x88); install the pickup handlers (free 0207fcd8, 0207fa7c, release
 * 0207fab0, show 0207fb8c, teardown 0207fa90, load 0207fac0, hit 0207fc40, 0207fcbc,
 * 0207fcc4, position 0207fcd0), tag the class 0x10 and clear the mission-flag base (+0x86 =
 * 0xffff, resolved when the first piece spawns). */
typedef signed char    s8;
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct Ov015PickupParams {
    const char *pModel;       /* 0x00: may be 0 */
    const char *pSequence;    /* 0x04 */
    int  nHeight;             /* 0x08 */
    s8   nParam82;            /* 0x0c */
    u8   pad_0d;
    short nParam7c;           /* 0x0e */
    short nParam7e;           /* 0x10 */
    short nParam80;           /* 0x12 */
    s8   nStepInit;           /* 0x14 */
    u8   pad_15[3];
    int  nParam88;            /* 0x18 */
    u8   nKind;               /* 0x1c */
    u8   pad_1d[3];
} Ov015PickupParams;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);
extern void func_ov015_0207fcd8(void);
extern void func_ov015_0207fa7c(void);
extern void func_ov015_0207fab0(void);
extern void func_ov015_0207fb8c(void);
extern void func_ov015_0207fa90(void);
extern void func_ov015_0207fac0(void);
extern void func_ov015_0207fc40(void);
extern void func_ov015_0207fcbc(void);
extern void func_ov015_0207fcc4(void);
extern void func_ov015_0207fcd0(void);

void *func_ov015_020800d4(void *pCtx, const Ov015PickupParams *pParams)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x8c, 0x154, pCtx);
    pTable[0x58] = 0;
    if (pParams->pModel != 0) {
        strncpy(pTable + 0x58, pParams->pModel, 0x10);
    }
    pTable[0x68] = 0;
    strncpy(pTable + 0x68, pParams->pSequence, 0x10);
    *(int *)(pTable + 0x78) = pParams->nHeight;
    *(s8 *)(pTable + 0x82) = pParams->nParam82;
    *(short *)(pTable + 0x7c) = pParams->nParam7c;
    *(short *)(pTable + 0x7e) = pParams->nParam7e;
    *(short *)(pTable + 0x80) = pParams->nParam80;
    *(int *)(pTable + 0x88) = pParams->nParam88;
    *(u8 *)(pTable + 0x84) = pParams->nKind;
    *(s8 *)(pTable + 0x83) = pParams->nStepInit;
    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = (int)func_ov015_0207fcd8;
    *(int *)(pTable + 0x08) = (int)func_ov015_0207fa7c;
    *(int *)(pTable + 0x0c) = (int)func_ov015_0207fab0;
    *(int *)(pTable + 0x10) = (int)func_ov015_0207fb8c;
    *(int *)(pTable + 0x14) = (int)func_ov015_0207fa90;
    *(int *)(pTable + 0x18) = (int)func_ov015_0207fac0;
    *(int *)(pTable + 0x1c) = 0;
    *(int *)(pTable + 0x20) = (int)func_ov015_0207fc40;
    *(int *)(pTable + 0x24) = (int)func_ov015_0207fcbc;
    *(int *)(pTable + 0x28) = (int)func_ov015_0207fcc4;
    *(int *)(pTable + 0x2c) = (int)func_ov015_0207fcd0;
    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x3c) = 0;
    *(u16 *)(pTable + 0x4c) = 0x10;
    *(u16 *)(pTable + 0x86) = 0xffff;
    return pTable;
}
