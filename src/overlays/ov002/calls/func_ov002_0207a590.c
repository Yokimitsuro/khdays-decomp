typedef unsigned short u16;

/* The descriptor the caller fills in for this class. */
typedef struct {
    int nOwnerArg;                  /* +0x00 */
    signed char bSlotKind;          /* +0x04 */
    unsigned char bPad0[3];         /* +0x05 */
    const char *pName;              /* +0x08 */
    signed char bKind;              /* +0x0c */
    unsigned char bPad1[3];         /* +0x0d */
    int nExtraA;                    /* +0x10 */
    int nExtraB;                    /* +0x14 */
    int nExtraC;                    /* +0x18 */
} Ov002PieceClassDesc;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);

extern void func_ov002_0207a3fc(void);
extern void func_ov002_0207a4b8(void);
extern void func_ov002_0207a3e4(void);
extern void func_ov002_0207a408(void);
extern void func_ov002_0207a574(void);
extern void func_ov002_0207a4f8(void);
extern void func_ov002_0207a500(void);
extern void func_ov002_0207a56c(void);
extern void func_ov002_0207a564(void);
extern void func_ov002_0207a57c(void);

/* Create the table that owns one class of placed piece.
 *
 * Allocates the 0x7c byte table together with room for 0x1b0 byte elements,
 * blanks the name and copies the descriptor's one over it when there is one,
 * copies the rest of the descriptor, stamps the unset track marker and
 * installs the class's ten handlers.
 */
void *func_ov002_0207a590(void *pCtx, const Ov002PieceClassDesc *pDesc)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x7c, 0x1b0, pCtx);

    *(unsigned char *)(pTable + 0x58) = 0;
    if (pDesc->pName != 0) {
        strncpy(pTable + 0x58, pDesc->pName, 0x10);
    }

    *(signed char *)(pTable + 0x78) = pDesc->bKind;
    *(int *)(pTable + 0x6c) = pDesc->nExtraA;
    *(int *)(pTable + 0x70) = pDesc->nExtraB;
    *(int *)(pTable + 0x74) = pDesc->nExtraC;
    *(signed char *)(pTable + 0x79) = pDesc->bSlotKind;
    *(int *)(pTable + 0x68) = pDesc->nOwnerArg;
    *(signed char *)(pTable + 0x7a) = -1;

    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = 0;
    *(int *)(pTable + 0x0c) = (int)func_ov002_0207a3fc;
    *(int *)(pTable + 0x10) = (int)func_ov002_0207a4b8;
    *(int *)(pTable + 0x14) = (int)func_ov002_0207a3e4;
    *(int *)(pTable + 0x18) = (int)func_ov002_0207a408;
    *(int *)(pTable + 0x1c) = (int)func_ov002_0207a574;
    *(int *)(pTable + 0x20) = 0;
    *(int *)(pTable + 0x24) = 0;
    *(int *)(pTable + 0x2c) = (int)func_ov002_0207a4f8;
    *(int *)(pTable + 0x30) = (int)func_ov002_0207a500;
    *(int *)(pTable + 0x34) = (int)func_ov002_0207a56c;
    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x40) = (int)func_ov002_0207a564;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x3c) = (int)func_ov002_0207a57c;
    *(u16 *)(pTable + 0x4c) = 6;

    return pTable;
}
