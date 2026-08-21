typedef unsigned short u16;

/* What the caller hands over to describe one class of timed element. */
typedef struct {
    const char *pName;              /* +0x00 */
    int nOwnerArg;                  /* +0x04 */
    signed char bKind;              /* +0x08 */
    char pad09;
    short nParamA;                  /* +0x0a */
    short nParamB;                  /* +0x0c */
    short nParamC;                  /* +0x0e */
    int nTrackLimit0;               /* +0x10 */
    int nTrackLimit1;               /* +0x14 */
    u16 wLimit;                     /* +0x18 */
    short nResId;                   /* +0x1a */
    short nResIdB;                  /* +0x1c */
    short nResIdC;                  /* +0x1e */
    int nExtraA;                    /* +0x20 */
    int nExtraB;                    /* +0x24 */
} Ov002ElementClassDesc;            /* 0x28 */

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);

extern void func_ov002_020790dc(void);
extern void func_ov002_02079104(void);
extern void func_ov002_02079224(void);
extern void func_ov002_020790f8(void);
extern void func_ov002_02079110(void);
extern void func_ov002_020792f0(void);
extern void func_ov002_02079398(void);
extern void func_ov002_02079400(void);
extern void func_ov002_02079468(void);
extern void func_ov002_02079268(void);
extern void func_ov002_02079470(void);

/* Create the table that owns one class of timed element.
 *
 * Allocates the 0x8c byte table together with room for 0x1bc byte elements,
 * copies the class name and the descriptor's fields into it, and installs the
 * class's eleven handlers. A negative first resource id means the class has
 * none, and all three ids are stamped -1.
 */
void *func_ov002_020795b4(void *pCtx, const Ov002ElementClassDesc *pDesc)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x8c, 0x1bc, pCtx);

    strncpy(pTable + 0x58, pDesc->pName, 0x10);

    *(int *)(pTable + 0x84) = pDesc->nExtraA;
    *(int *)(pTable + 0x88) = pDesc->nExtraB;
    *(int *)(pTable + 0x68) = pDesc->nOwnerArg;
    *(signed char *)(pTable + 0x6c) = pDesc->bKind;
    *(short *)(pTable + 0x6e) = pDesc->nParamA;
    *(short *)(pTable + 0x70) = pDesc->nParamB;
    *(short *)(pTable + 0x72) = pDesc->nParamC;
    *(int *)(pTable + 0x74) = pDesc->nTrackLimit0;
    *(int *)(pTable + 0x78) = pDesc->nTrackLimit1;
    *(u16 *)(pTable + 0x7c) = pDesc->wLimit;

    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = (int)func_ov002_020790dc;
    *(int *)(pTable + 0x0c) = (int)func_ov002_02079104;
    *(int *)(pTable + 0x10) = (int)func_ov002_02079224;
    *(int *)(pTable + 0x14) = (int)func_ov002_020790f8;
    *(int *)(pTable + 0x18) = (int)func_ov002_02079110;
    *(int *)(pTable + 0x1c) = (int)func_ov002_020792f0;
    *(int *)(pTable + 0x20) = 0;
    *(int *)(pTable + 0x24) = (int)func_ov002_02079398;
    *(int *)(pTable + 0x28) = (int)func_ov002_02079400;
    *(int *)(pTable + 0x2c) = (int)func_ov002_02079468;
    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = (int)func_ov002_02079268;
    *(int *)(pTable + 0x3c) = (int)func_ov002_02079470;
    *(u16 *)(pTable + 0x4c) = 3;

    /* Writing the third id in both arms is what the ROM does: routing it
     * through one shared local instead makes mwcc place the descriptor offset
     * sixty instructions early, into the load-use stall of the copy block. */
    if (pDesc->nResId >= 0) {
        *(short *)(pTable + 0x7e) = pDesc->nResId;
        *(short *)(pTable + 0x80) = pDesc->nResIdB;
        *(short *)(pTable + 0x82) = pDesc->nResIdC;
    } else {
        *(short *)(pTable + 0x7e) = -1;
        *(short *)(pTable + 0x80) = -1;
        *(short *)(pTable + 0x82) = -1;
    }

    return pTable;
}
