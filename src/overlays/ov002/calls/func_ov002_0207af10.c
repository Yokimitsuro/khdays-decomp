typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern char *func_ov002_02076a38(void *pClass, int nSlot);
extern int func_ov002_0207285c(int nBucket);
extern unsigned int strlen(const char *s);
extern void func_0201f924(void *pDst, const void *pSrc);
extern void func_ov002_02076480(int nBucket, char *pEntry);
extern void func_ov002_0207aac8(void);

/* Spawn one spare entry of a class.
 *
 * Claims an entry, puts it at the caller's position and takes the two texts:
 * with neither there is nothing to say, with only a line the name is blank.
 * The count comes in signed - a negative one means the entry is held rather
 * than counted - and two flags arm the park handler and the wide slot. The
 * state machine is installed last and the entry is pushed into its bucket.
 */
char *func_ov002_0207af10(void *pClass, int nSlot, int nBucket, const Vec3 *pPos,
                          u16 wStateField, unsigned char bStateWidth,
                          signed char bQueuedWidth, signed char nCount,
                          const char *pName, const char *pLine,
                          int nParamA, int nParamB, int bArm, int bWide)
{
    char *pEntry;

    pEntry = func_ov002_02076a38(pClass, nSlot);
    func_ov002_0207285c(nBucket);

    *(Vec3 *)(pEntry + 0x1c) = *pPos;

    *(int *)(pEntry + 0x28) = nParamB;
    *(int *)(pEntry + 0x44) = nParamA;

    if (pName == 0 && pLine == 0) {
        *(signed char *)(pEntry + 0x37) = 0;
        *(signed char *)(pEntry + 0x2f) = *(signed char *)(pEntry + 0x37);
    } else {
        if (pName == 0) {
            *(signed char *)(pEntry + 0x2f) = 0;
        } else {
            strlen(pName);
            func_0201f924(pEntry + 0x2f, pName);
        }
        strlen(pLine);
        func_0201f924(pEntry + 0x37, pLine);
    }

    *(unsigned char *)(pEntry + 0x2c) = 0;
    *(unsigned char *)(pEntry + 0x3f) = 0;
    *(signed char *)(pEntry + 0x2e) = bQueuedWidth;

    if (nCount < 0) {
        *(signed char *)(pEntry + 0x40) = 0x10;
        *(signed char *)(pEntry + 0x40) |= 1;
    } else {
        *(signed char *)(pEntry + 0x40) = nCount & 0xf;
    }

    if (bArm != 0) {
        *(signed char *)(pEntry + 0x40) |= 0x40;
    }
    if (bWide != 0) {
        *(signed char *)(pEntry + 0x40) |= 0x20;
    }

    *(unsigned char *)(pEntry + 0x2d) = (unsigned char)nSlot;

    *(unsigned char *)(pEntry + 0x10) = (unsigned char)nBucket;
    *(int *)(pEntry + 0x0c) = (int)func_ov002_0207aac8;
    *(u16 *)(pEntry + 0x12) |= 8;

    *(u16 *)(pEntry + 0x14) = wStateField;
    *(unsigned char *)(pEntry + 0x16) = bStateWidth;
    *(unsigned char *)(pEntry + 0x17) = *(signed char *)(pEntry + 0x2e);

    func_ov002_02076480(nBucket, pEntry);
    return pEntry;
}
