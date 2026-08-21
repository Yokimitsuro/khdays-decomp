typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern u8 data_0204c240;

extern int func_ov002_0206da70(void *pName);
extern void func_0202b930(char *pObj, int nRes, int a, int b);
extern void func_0202b450(char *pNode, Vec3 *pPos);
extern int func_ov002_0207c6c0(u16 *pAnim);
extern void func_ov002_0207c618(short *pAnim, int nTrack, int nFrame);
extern void func_0202af1c(u16 *pAnim);
extern void func_0202af2c(u16 *pAnim);
extern unsigned int func_020235d0(u16 nId, u8 nSlot);
extern void func_0202bedc(char *pObj, int bOn);
extern void func_ov002_0206ae64(int nKind, Vec3 *pPos, int nParam);

/* Bring an actor element's model back after its owner has been rebound.
 *
 * The cached position is read first because binding the model moves the node,
 * then the node goes back there and the first placement remembers the angle.
 * The pose the model reports decides the track: one particular pose, with the
 * element ready and the global gate open, plays the alternate track instead of
 * the idle one. The object follows the game-state bit again, and the element's
 * pending bit is dropped once the work is done.
 */
void func_ov002_0207b230(char *pElement)
{
    Vec3 vPos;
    const Vec3 *pCached;
    void *pOwnerName;
    int nState;
    int bVisible;
    u16 wAngle;

    pOwnerName = *(char **)(pElement + 8) + 0x58;
    pCached = (const Vec3 *)(pElement + 0x1c);
    vPos.x = pCached->x;
    vPos.y = pCached->y;
    vPos.z = pCached->z;
    *(signed char *)(pElement + 0x1b8) = 0;

    func_0202b930(pElement + 0x2c, func_ov002_0206da70(pOwnerName), 1, 4);

    wAngle = *(u16 *)(pElement + 0x18);
    if ((*(unsigned int *)(pElement + 0x38) & 0x20) == 0) {
        *(u16 *)(pElement + 0xb8) = wAngle;
        *(u16 *)(pElement + 0x3c) |= 0x20;
    }

    func_0202b450(pElement + 0x38, &vPos);

    *(signed char *)(pElement + 0x1b4) =
        (signed char)func_ov002_0207c6c0((u16 *)(pElement + 0x3c));

    if (*(signed char *)(pElement + 0x1b4) == 3
        && (*(u8 *)(pElement + 0x1b5) & 1) == 0
        && (data_0204c240 & 4) == 0
        && (*(u8 *)(pElement + 0x1b5) & 0x80) != 0) {
        *(signed char *)(pElement + 0x1b8) = 2;
    }

    func_ov002_0207c618((short *)(pElement + 0x3c),
                        *(signed char *)(pElement + 0x1b8), 0);

    if (*(signed char *)(pElement + 0x1b8) != 0) {
        func_0202af1c((u16 *)(pElement + 0x3c));
        *(u8 *)(pElement + 0x1b5) |= 2;
    } else {
        func_0202af2c((u16 *)(pElement + 0x3c));
        *(u8 *)(pElement + 0x1b5) |= 1;
    }

    nState = func_020235d0(*(u16 *)(pElement + 0x14),
                           *(u8 *)(pElement + 0x16));
    func_0202bedc(pElement + 0x2c, (nState & 1) != 0);

    bVisible = (func_020235d0(*(u16 *)(pElement + 0x14),
                              *(u8 *)(pElement + 0x16)) & 1) != 0;
    if (bVisible) {
        func_ov002_0206ae64(1, &vPos, 0);
    }

    *(u8 *)(pElement + 0x1b5) &= ~0x80;
}
