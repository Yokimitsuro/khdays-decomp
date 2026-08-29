typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;

typedef struct Ov002Vec3 {
    int x, y, z;
} Ov002Vec3;

extern char *func_ov002_02076a38(char *pClass, int nSlot);
extern int func_ov002_0207c4c0(void *pObj, int nNode, void *pOut,
                                int nUnused, int nKind, int nParamA,
                                int nParamB, int nParamC,
                                int nAngle, int nFlag);
extern void func_ov002_0207c53c(Ov002Vec3 *pOut, Ov002Vec3 *pPos, int *pIn);
extern void func_0202b450(char *pNode, Ov002Vec3 *pPos);
extern void func_02029438(void *pNode, int nIndex, int nValue);
extern void func_ov002_02076480(int nBucket, char *pPiece);
extern void func_ov002_0207cea4(void);

/* Bring one piece of a class up and put it on the board.
 *
 * The piece takes its placement from the class it came from, is moved to the
 * point the caller gives and is handed the class's own per-frame hook.  A
 * class whose kind is neither 0 nor 3 also gets its extra node switched on.
 * The finished piece is registered in the caller's bucket and handed back.
 */
char *func_ov002_0207a650(char *pClass, u16 wSlot, u16 wBucket,
                          u16 wStateField, u8 bStateWidth, Ov002Vec3 *pPos,
                          s16 nAngle)
{
    Ov002Vec3 vOut;
    int aSetup[5];
    char *pPiece;

    pPiece = func_ov002_02076a38(pClass, wSlot);
    func_ov002_0207c4c0(pPiece, (int)(pPiece + 0x1c), aSetup, wSlot,
                        *(s8 *)(pClass + 0x78),
                        *(int *)(pClass + 0x6c),
                        *(int *)(pClass + 0x70),
                        *(int *)(pClass + 0x74),
                        nAngle, 1);
    func_ov002_0207c53c(&vOut, pPos, aSetup);
    *(int *)(pPiece + 0x19c) = 0x1000;
    func_0202b450(pPiece + 0x28, pPos);

    *(s16 *)(pPiece + 0x18) = nAngle;
    *(u8 *)(pPiece + 0x10) = (u8)wBucket;
    *(void **)(pPiece + 0x0c) = (void *)func_ov002_0207cea4;
    *(s16 *)(pPiece + 0x14) = (s16)wStateField;
    *(u8 *)(pPiece + 0x16) = bStateWidth;
    *(u8 *)(pPiece + 0x17) = 0;
    *(s8 *)(pPiece + 0x1a0) = *(s8 *)(pClass + 0x79);

    if (*(s8 *)(pClass + 0x78) != 3 && *(s8 *)(pClass + 0x78) != 0) {
        func_02029438(pPiece + 0x138, 1, 3);
    }

    *(s16 *)(pPiece + 0x1a2) = 0;
    func_ov002_02076480(wBucket, pPiece);
    return pPiece;
}
