typedef unsigned short u16;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_ov002_0206da70(void *pName);
extern void func_0202b930(char *pObj, int nRes, int a, int b);
extern void func_0202b450(char *pNode, Vec3 *pPos);
extern void func_ov002_0207c618(short *pAnim, int nBlend, int nFrame);
extern void func_0202af2c(u16 *pNode);
extern int func_020235d0(u16 nId, unsigned char nSlot);
extern void func_0202bedc(char *pObj, int bOn);
extern void func_0202bf18(char *pObj, int bFlag, int nParam);

/* Bring an element's model back after its owner has been rebound.
 *
 * The cached position is read first because binding the model moves the node,
 * then the node is put back there, the first placement remembers the angle,
 * the element is marked as driving its table, its track is blended in from
 * frame zero, and the object follows the game-state bit again.
 */
void func_ov002_0207a408(char *pElement)
{
    char *pOwner;
    Vec3 vPos;
    u16 wAngle;
    int nState;

    pOwner = *(char **)(pElement + 8);

    if (*(signed char *)(pOwner + 0x58) != 0) {
        vPos = *(Vec3 *)(pElement + 0xd0);

        func_0202b930(pElement + 0x1c, func_ov002_0206da70(pOwner + 0x58),
                      1, 4);
        func_0202b450(pElement + 0x28, &vPos);

        wAngle = *(u16 *)(pElement + 0x18);
        if ((*(unsigned int *)(pElement + 0x28) & 0x20) == 0) {
            *(u16 *)(pElement + 0xa8) = wAngle;
            *(u16 *)(pElement + 0x2c) |= 0x20;
        }

        *(u16 *)(pElement + 0x12) |= 4;

        func_ov002_0207c618((short *)(pElement + 0x2c),
                            *(signed char *)(pElement + 0x1a0), 0);
        func_0202af2c((u16 *)(pElement + 0x2c));

        nState = func_020235d0(*(u16 *)(pElement + 0x14),
                               *(unsigned char *)(pElement + 0x16));
        func_0202bedc(pElement + 0x1c, (nState & 1) != 0);

        func_0202bf18(pElement + 0x1c,
                      (*(u16 *)(pElement + 0x12) & 0x100) != 0,
                      *(short *)(pElement + 0x1a2));
    }
}
