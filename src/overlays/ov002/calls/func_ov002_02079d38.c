typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern char *func_ov002_02076a38(char *pClass, int nSlot);
extern int func_ov002_0207285c(int nSlot);
extern int func_0202b87c(int nNode, int nZero, void *pObj, void *pParams,
                         int nFlag);
extern int func_0202c3e4(u16 nId, int nSpot, Vec3 *pOut);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *ab);
extern void func_0202b450(char *pNode, Vec3 *pPos);
extern short func_0202c404(u16 nId, int nSpot);
extern char *strncpy(char *pDst, const char *pSrc, unsigned int nSize);
extern void func_ov002_02076480(int nBucket, char *pElement);
extern void *func_ov002_02079b44(char *pElement);

/* Spawn one actor element of a class.
 *
 * Claims a pool entry, attaches its object and puts it either at a named spot
 * of the slot's context - offset by the caller's vector when there is one -
 * or straight at the caller's position and angle. The owner's cached vector is
 * copied in, the slot, handler, game-state descriptor and name are stamped,
 * and the class's kind decides which of the four modes get a track.
 */
char *func_ov002_02079d38(char *pClass, int nSlot, int nBucket,
                          u16 wStateField, unsigned char bStateWidth,
                          const char *pName, signed char bTrackIndex,
                          int nSpot, Vec3 *pPos, const Vec3 *pBound,
                          short nAngle)
{
    char *pElement;
    char *pOwner;
    int nId;
    signed char nKind;
    Vec3 vSpot;

    pElement = func_ov002_02076a38(pClass, nSlot);
    pOwner = *(char **)(pElement + 8);
    nId = func_ov002_0207285c(nBucket);

    func_0202b87c((int)(pElement + 0x1c), 0, pElement, 0, 1);

    if (nSpot != 0 && func_0202c3e4((u16)nId, nSpot, &vSpot) != 0) {
        if (pPos != 0) {
            VEC_Add(&vSpot, pPos, &vSpot);
        }
        func_0202b450(pElement + 0x28, &vSpot);
        *(short *)(pElement + 0x18) = func_0202c404((u16)nId, nSpot);
    } else {
        func_0202b450(pElement + 0x28, pPos);
        *(short *)(pElement + 0x18) = nAngle;
    }

    if (*(signed char *)(pOwner + 0x58) != 0) {
        *(Vec3 *)(pElement + 0xdc) = *pBound;
    }

    *(unsigned char *)(pElement + 0x10) = (unsigned char)nBucket;
    *(int *)(pElement + 0x0c) = (int)func_ov002_02079b44;
    *(u16 *)(pElement + 0x14) = wStateField;
    *(unsigned char *)(pElement + 0x16) = bStateWidth;
    *(unsigned char *)(pElement + 0x17) = 0;

    if (pName != 0) {
        strncpy(pElement + 0x1a0, pName, 0x20);
    } else {
        *(unsigned char *)(pElement + 0x1a0) = 0;
    }

    *(signed char *)(pElement + 0x1c0) = bTrackIndex;
    *(unsigned char *)(pElement + 0x1c1) = 0;

    nKind = *(signed char *)(pOwner + 0x80);
    switch (nKind) {
    case 1:
        *(signed char *)(pElement + 0x1c3) = -1;
        *(signed char *)(pElement + 0x1c4) = -1;
        *(signed char *)(pElement + 0x1c5) = 0;
        *(signed char *)(pElement + 0x1c6) = -1;
        break;
    case 2:
        *(signed char *)(pElement + 0x1c3) = 0;
        *(signed char *)(pElement + 0x1c4) = -1;
        *(signed char *)(pElement + 0x1c5) = 1;
        *(signed char *)(pElement + 0x1c6) = -1;
        break;
    case 4:
        *(signed char *)(pElement + 0x1c3) = 0;
        *(signed char *)(pElement + 0x1c4) = 1;
        *(signed char *)(pElement + 0x1c5) = 2;
        *(signed char *)(pElement + 0x1c6) = 3;
        break;
    }

    func_ov002_02076480(nBucket, pElement);
    return pElement;
}
