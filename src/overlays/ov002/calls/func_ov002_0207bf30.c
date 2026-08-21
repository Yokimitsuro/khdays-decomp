typedef unsigned short u16;
typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

extern int func_ov002_0206da70(void *pName);
extern void func_0202a634(char *pNode, int nRes, int a, int b);
extern void func_ov002_0207be34(char *pElement, short *pAnim, int nTrack,
                                int nParamA, int nParamB, int bEffect);
extern void func_0203355c(int nId);

/* Bring a line element's second model up.
 *
 * The element is marked active first. With no model named by the owner there is
 * nothing to build, but the effect below still runs. Otherwise the node's
 * position is kept across the bind, put back afterwards, the angle is carried
 * over and the model is marked placed before its track starts with the values
 * the element already holds.
 */
void func_ov002_0207bf30(char *pElement)
{
    char *pOwner;
    Vec3 vPos;

    pOwner = *(char **)(pElement + 8);
    *(u16 *)(pElement + 0x12) |= 4;

    if (*(signed char *)(pOwner + 0x58) != 0) {
        vPos = *(Vec3 *)(pElement + 0xe0);

        func_0202a634(pElement + 0x1b0,
                      func_ov002_0206da70(pOwner + 0x58), 1, 4);

        *(Vec3 *)(pElement + 0x254) = vPos;
        *(u16 *)(pElement + 0x22c) = *(u16 *)(pElement + 0x18);
        *(u16 *)(pElement + 0x1b0) |= 0x20;

        func_ov002_0207be34(pElement, (short *)(pElement + 0x1b0),
                            *(u8 *)(pElement + 0x2c0),
                            *(int *)(pElement + 0x2bc),
                            *(int *)(pElement + 0x2b8), 0);
    }

    if (*(short *)(pOwner + 0x74) >= 0) {
        func_0203355c(*(short *)(pOwner + 0x74));
    }
}
