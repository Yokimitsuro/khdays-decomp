typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern u8 data_0204c240;

extern char *func_ov002_02076a38(void *pClass, int nSlot);
extern void func_0202b87c(char *pObj, int a, void *pOwner, int c, int d);
extern void func_0202b450(char *pNode, const Vec3 *pPos);
extern void func_ov002_02076480(int nBucket, char *pElement);
extern void func_0201f924(void *pDst, const void *pSrc);

extern void func_ov002_0207b9f4(void);
extern void func_ov002_0207b438(void);

/* Spawn one line element of a class.
 *
 * Claims an entry, binds its object, puts the node at the caller's position and
 * keeps that position where the element can find it again. The step handler
 * depends on the global gate: with it closed the element gathers actors first,
 * with it open it goes straight to the prompt. The element starts with its
 * pending bit raised, no pose and no progress, and takes the caller's prompt
 * text when there is one.
 */
char *func_ov002_0207bd88(char *pClass, int nSlot, int nBucket, u16 wStateField,
                          u8 bStateWidth, const Vec3 *pPos, short nAngle,
                          const void *pText)
{
    char *pElement;
    void (*pfnStep)(void);

    pElement = func_ov002_02076a38(pClass, nSlot);

    func_0202b87c(pElement + 0x2c, 0, pElement, 0, 0);

    *(int *)(pElement + 0x1ac) = 0x1000;
    func_0202b450(pElement + 0x38, pPos);

    *(short *)(pElement + 0x18) = nAngle;
    *(Vec3 *)(pElement + 0x1c) = *(Vec3 *)(pElement + 0xe0);

    *(int *)(pElement + 0x28) = *(short *)(pClass + 0x68);
    *(u8 *)(pElement + 0x10) = (u8)nBucket;

    if ((data_0204c240 & 4) != 0) {
        pfnStep = func_ov002_0207b9f4;
    } else {
        pfnStep = func_ov002_0207b438;
    }
    *(int *)(pElement + 0x0c) = (int)pfnStep;

    *(u16 *)(pElement + 0x14) = wStateField;
    *(u8 *)(pElement + 0x16) = bStateWidth;
    *(u8 *)(pElement + 0x17) = 0;

    func_ov002_02076480(nBucket, pElement);

    *(u8 *)(pElement + 0x1b5) = 0x80;
    *(signed char *)(pElement + 0x1b4) = -1;
    *(int *)(pElement + 0x1b0) = 0;

    if (pText != 0) {
        func_0201f924(pElement + 0x1bb, pText);
    }

    return pElement;
}
