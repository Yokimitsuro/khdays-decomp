typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

/* The 20 byte placement record the node call reads. Only the first three
 * fields are set here. */
typedef struct {
    int nKind;                      /* +0x00 */
    int nParamB;                    /* +0x04 */
    int nParamA;                    /* +0x08 */
    int nParamC;                    /* +0x0c */
    int nAngle;                     /* +0x10 */
} Ov002PlaceParams;

extern char *func_ov002_02076a38(char *pClass, int nSlot);
extern int func_0202b87c(int nNode, int nZero, void *pObj,
                         Ov002PlaceParams *pParams, int nFlag);
extern void func_0202b450(char *pNode, Vec3 *pPos);
extern int func_ov002_02077b30(void);
extern void func_ov002_02076480(int nBucket, char *pElement);
extern void func_ov002_0207a0c8(char *pElement);

/* Spawn one timed element of a class.
 *
 * Claims a pool entry, places its node with a fixed pair of placement
 * parameters, moves it to the requested position and remembers that position
 * and angle. The key, the claimed unit and the slot are stamped, the element
 * starts in state 3, and the per-frame handler is installed before the node
 * goes into its bucket.
 */
void func_ov002_0207a32c(char *pClass, int nSlot, int nBucket, Vec3 *pPos,
                         short nAngle, u16 wStateField,
                         unsigned char bStateWidth, short nKey)
{
    char *pElement;
    Ov002PlaceParams place;
    Vec3 vPos;

    pElement = func_ov002_02076a38(pClass, nSlot);

    place.nParamA = 0x800;
    place.nParamB = 0xb5c;
    place.nKind = 0;
    func_0202b87c((int)(pElement + 0x2c), 0, pElement, &place, 1);

    vPos = *pPos;
    func_0202b450(pElement + 0x38, &vPos);

    *(short *)(pElement + 0x18) = nAngle;
    *(Vec3 *)(pElement + 0x1c) = *pPos;
    *(int *)(pElement + 0x28) = place.nParamA;

    *(u16 *)(pElement + 0x1b6) = nKey;
    *(int *)(pElement + 0x1b0) = 0;

    *(unsigned char *)(pElement + 0x1b9) =
        (unsigned char)func_ov002_02077b30();
    *(unsigned char *)(pElement + 0x1ba) = (unsigned char)nSlot;
    *(unsigned char *)(pElement + 0x1b4) = 3;

    *(unsigned char *)(pElement + 0x10) = (unsigned char)nBucket;
    *(int *)(pElement + 0x0c) = (int)func_ov002_0207a0c8;
    *(u16 *)(pElement + 0x12) |= 8;
    *(u16 *)(pElement + 0x14) = wStateField;
    *(unsigned char *)(pElement + 0x16) = bStateWidth;
    *(unsigned char *)(pElement + 0x17) = 1;

    func_ov002_02076480(nBucket, pElement);
}
