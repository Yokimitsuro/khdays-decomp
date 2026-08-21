typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

extern void *func_ov002_0206da70(char *pChannel);
extern void func_0202b930(char *pObj, void *pEntry, int nA, int nB);
extern void func_0202b450(char *pNode, VecFx32 *pPos);
extern int func_ov002_0207c6c0(char *pNode);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_ov002_0207903c(char *pElement);
extern void func_0202bedc(char *pObj, int bOn);
extern void func_0203355c(int nId);

/* Bring a timed element on screen.
 *
 * Binds the owner's channel entry to the element's object, remembers the
 * element's own width the first time the node is placed, moves the node to the
 * spawn position built at +0xe0, and then reads the element's game-state field
 * three times: once for the track index, once for the visibility bit the object
 * follows, and once for the bit that forces it hidden. Slot 2 is never forced.
 */
void func_ov002_02079110(char *pElement)
{
    char *pOwner;
    VecFx32 vec;
    void *pEntry;
    unsigned int nState;
    u16 wWidth;

    pOwner = *(char **)(pElement + 8);
    vec = *(VecFx32 *)(pElement + 0xe0);

    pEntry = func_ov002_0206da70(pOwner + 0x58);
    func_0202b930(pElement + 0x2c, pEntry, 1, 4);

    wWidth = *(u16 *)(pElement + 0x18);
    if ((*(int *)(pElement + 0x38) & 0x20) == 0) {
        *(u16 *)(pElement + 0xb8) = wWidth;
        *(u16 *)(pElement + 0x3c) |= 0x20;
    }

    func_0202b450(pElement + 0x38, &vec);

    *(unsigned char *)(pElement + 0x1ba) =
        (unsigned char)func_ov002_0207c6c0(pElement + 0x3c);

    nState = func_020235d0(*(u16 *)(pElement + 0x14),
                           *(unsigned char *)(pElement + 0x16));
    *(unsigned char *)(pElement + 0x1b8) =
        (unsigned char)((((nState & 0xfffe) << 15) >> 16) & 1);

    *(u16 *)(pElement + 0x12) |= 4;

    func_ov002_0207903c(pElement);

    nState = func_020235d0(*(u16 *)(pElement + 0x14),
                           *(unsigned char *)(pElement + 0x16));
    func_0202bedc(pElement + 0x2c, (nState & 1) != 0);

    if (*(unsigned char *)(pElement + 0x16) == 2) {
        nState = 0;
    } else {
        nState = ((unsigned int)(func_020235d0(*(u16 *)(pElement + 0x14),
                                               *(unsigned char *)(pElement + 0x16))
                                 & 0xfffe) << 15) >> 16;
        nState &= 2;
    }

    if (nState != 0) {
        *(unsigned char *)(pElement + 0x1bb) |= 0x40;
        func_0202bedc(pElement + 0x2c, 0);
    } else {
        *(unsigned char *)(pElement + 0x1bb) &= ~0x40;
    }

    if (*(short *)(pOwner + 0x7e) >= 0) {
        func_0203355c(*(short *)(pOwner + 0x7e));
    }

    if (*(int *)(pOwner + *(unsigned char *)(pElement + 0x1b8) * 4 + 0x74) == 0) {
        *(u16 *)(pElement + 0x12) &= ~8;
    } else {
        *(u16 *)(pElement + 0x12) |= 8;
    }
}
