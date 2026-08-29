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
extern void func_ov002_02076480(int nBucket, char *pElement);
extern void func_ov002_0207c0ac(void);

/* Spawn one travelling element of a class.
 *
 * Claims a pool entry for the slot, places its scene node with the class's
 * placement parameters, builds the start position from the requested one and
 * syncs the child actor. Then stamps the angle, position, extent, bucket, the
 * travel step hook, the travel parameter and the state field descriptor. A
 * negative travel parameter starts the element hidden. The travel state is
 * cleared out - no step, no track, no distance and no entry - and the element
 * is pushed into its bucket.
 */
char *func_ov002_0207c3bc(char *pClass, u16 wSlot, u16 wBucket,
                          u16 wStateField, u8 bStateWidth, Ov002Vec3 *pPos,
                          s16 nAngle, s16 nTravelParam)
{
    Ov002Vec3 vStart;
    int aPlace[5];
    char *pElement;

    pElement = func_ov002_02076a38(pClass, wSlot);
    func_ov002_0207c4c0(pElement, (int)(pElement + 0x2c), aPlace, wSlot,
                        *(s8 *)(pClass + 0x6c),
                        *(s16 *)(pClass + 0x6e),
                        *(s16 *)(pClass + 0x70),
                        *(s16 *)(pClass + 0x72),
                        nAngle, 1);
    func_ov002_0207c53c(&vStart, pPos, aPlace);
    func_0202b450(pElement + 0x38, pPos);

    *(s16 *)(pElement + 0x18) = nAngle;
    *(Ov002Vec3 *)(pElement + 0x1c) = vStart;
    *(int *)(pElement + 0x28) = aPlace[2];
    *(u8 *)(pElement + 0x10) = (u8)wBucket;
    *(void **)(pElement + 0x0c) = (void *)func_ov002_0207c0ac;
    *(s16 *)(pElement + 0x2c4) = nTravelParam;
    if (nTravelParam < 0) {
        *(u16 *)(pElement + 0x12) &= ~8;
    } else {
        *(u16 *)(pElement + 0x12) |= 8;
    }
    *(u8 *)(pElement + 0x17) = 1;
    *(s16 *)(pElement + 0x14) = (s16)wStateField;
    *(u8 *)(pElement + 0x16) = bStateWidth;
    *(u8 *)(pElement + 0x2c1) = 0;
    *(u8 *)(pElement + 0x2c0) = 0;
    *(int *)(pElement + 0x2bc) = 0;
    *(int *)(pElement + 0x2b8) = 0;
    *(u8 *)(pElement + 0x2c2) = 0xff;
    *(u8 *)(pElement + 0x2c3) = 0;

    func_ov002_02076480(wBucket, pElement);
    return pElement;
}
