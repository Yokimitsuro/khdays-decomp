typedef unsigned short u16;

/* The descriptor the caller fills in for one timed-element class. */
typedef struct {
    const char *pName;              /* +0x00 */
    int nOwnerArg;                  /* +0x04 */
} Ov002TimedClassDesc;

extern void *func_ov002_020769b0(int nTableSize, int nElementSize, void *pCtx);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);

extern void func_ov002_02079ec4(void);
extern void func_ov002_02079f50(void);
extern void func_ov002_02079eb0(void);
extern void func_ov002_02079ed0(void);
extern void func_ov002_02079f9c(void);
extern void func_ov002_0207a070(void);
extern void func_ov002_0207a0a8(void);
extern void func_ov002_0207a0b4(void);
extern void func_ov002_0207a0bc(void);

/* Create the table that owns one class of timed element.
 *
 * Allocates the 0x6c byte table together with room for 0x1bc byte elements,
 * blanks the name and copies the descriptor's one over it when there is one,
 * then installs the class's nine handlers.
 */
void *func_ov002_0207a29c(void *pCtx, const Ov002TimedClassDesc *pDesc)
{
    char *pTable;

    pTable = (char *)func_ov002_020769b0(0x6c, 0x1bc, pCtx);

    *(unsigned char *)(pTable + 0x58) = 0;
    if (pDesc->pName != 0) {
        strncpy(pTable + 0x58, pDesc->pName, 0x10);
    }

    *(int *)(pTable + 0x68) = pDesc->nOwnerArg;

    *(int *)(pTable + 0x00) = 0;
    *(int *)(pTable + 0x04) = 0;
    *(int *)(pTable + 0x08) = 0;
    *(int *)(pTable + 0x0c) = (int)func_ov002_02079ec4;
    *(int *)(pTable + 0x10) = (int)func_ov002_02079f50;
    *(int *)(pTable + 0x14) = (int)func_ov002_02079eb0;
    *(int *)(pTable + 0x18) = (int)func_ov002_02079ed0;
    *(int *)(pTable + 0x1c) = 0;
    *(int *)(pTable + 0x20) = (int)func_ov002_02079f9c;
    *(int *)(pTable + 0x24) = (int)func_ov002_0207a070;
    *(int *)(pTable + 0x28) = (int)func_ov002_0207a0a8;
    *(int *)(pTable + 0x2c) = (int)func_ov002_0207a0b4;
    *(int *)(pTable + 0x38) = 0;
    *(int *)(pTable + 0x44) = 0;
    *(int *)(pTable + 0x3c) = (int)func_ov002_0207a0bc;
    *(u16 *)(pTable + 0x4c) = 0xb;

    return pTable;
}
