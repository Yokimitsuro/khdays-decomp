typedef unsigned short u16;

/* The descriptor the caller fills in for one actor-element class. */
typedef struct {
    const char *pName;              /* +0x00 */
    short nParamA;                  /* +0x04 */
    short nParamB;                  /* +0x06 */
    short nParamC;                  /* +0x08 */
    short nPad;                     /* +0x0a */
    int nExtraA;                    /* +0x0c */
    int nExtraB;                    /* +0x10 */
    signed char bKind;              /* +0x14 */
} Ov002ActorClassDesc;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);

extern void func_ov002_02079974(void);
extern void func_ov002_020799b8(void);
extern void func_ov002_02079adc(void);
extern void func_ov002_020799a4(void);
extern void func_ov002_020799c4(void);
extern void func_ov002_02079b30(void);
extern void func_ov002_02079b38(void);

/* Create the table that owns one class of actor element.
 *
 * Allocates the 0x84 byte table together with room for 0x1d4 byte elements,
 * copies the descriptor's fields into it - the name only when there is one -
 * and installs the class's seven handlers.
 */
void *func_ov002_02079c94(void *pCtx, const Ov002ActorClassDesc *pDesc)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x84, 0x1d4, pCtx);

    if (pDesc->pName != 0) {
        strncpy(pTable + 0x58, pDesc->pName, 0x10);
    }

    *(short *)(pTable + 0x68) = pDesc->nParamA;
    *(short *)(pTable + 0x6a) = pDesc->nParamB;
    *(short *)(pTable + 0x6c) = pDesc->nParamC;
    *(signed char *)(pTable + 0x80) = pDesc->bKind;
    *(int *)(pTable + 0x7c) = pDesc->nExtraA;
    *(int *)(pTable + 0x74) = pDesc->nExtraB;

    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = (int)func_ov002_02079974;
    *(int *)(pTable + 0x0c) = (int)func_ov002_020799b8;
    *(int *)(pTable + 0x10) = (int)func_ov002_02079adc;
    *(int *)(pTable + 0x14) = (int)func_ov002_020799a4;
    *(int *)(pTable + 0x18) = (int)func_ov002_020799c4;
    *(int *)(pTable + 0x1c) = 0;
    *(int *)(pTable + 0x20) = 0;
    *(int *)(pTable + 0x24) = 0;
    *(int *)(pTable + 0x2c) = (int)func_ov002_02079b30;
    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x3c) = (int)func_ov002_02079b38;
    *(u16 *)(pTable + 0x4c) = 5;

    return pTable;
}
