typedef unsigned char u8;

extern const short data_ov002_0207e6fc[];

extern int func_ov002_0206dbbc(void);
extern int func_02030788(void);
extern int func_ov022_020882f8(void);
extern void *func_01fffde0(int nIndex);
extern int func_ov002_0207b134(char *pElement, void *pEntry);
extern int func_ov002_0206e6d0(void);
extern void func_ov002_0206bbb8(int nIndex, int nKind, int nValue);
extern int func_ov002_020766e0(void *pElement, void *pMsg, int nKind);
extern int func_ov002_0206b7a4(void);
extern void func_ov002_0206d928(int nMode);
extern void func_ov002_0207cea4(void);
extern int func_ov002_0206b758(void);
extern int func_01fffe14(void);
extern int func_ov022_02088474(int nIndex);
extern int func_ov002_02072754(int nHandle);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

/* Gather the actors an element wants and tell them to come over.
 *
 * While the element is waiting it looks at every entry that has not been
 * claimed yet: an actor in range is claimed, and unless the owner already has
 * it, it is sent walking to a distance that grows with how many have been
 * claimed so far. Only when every entry it looked at was in range does the
 * element start. On the second step it waits for the transition and hands over
 * to the idle handler. Whatever happened, each claimed actor that has not been
 * told yet is sent its message.
 */
void *func_ov002_0207b9f4(char *pElement)
{
    unsigned char aStart[6];
    unsigned char aMsg[6];
    char *pOwner;
    void *pEntry;
    int i;
    int bAllInRange;
    int nClaimed;
    int j;
    int nDist;
    int nSlot;

    pOwner = *(char **)(pElement + 8);

    switch (*(u8 *)(pElement + 0x1b6)) {
    case 0:
        if (func_ov002_0206dbbc() != 0 && func_02030788() == 0) {
            bAllInRange = 1;

            for (i = 0; i < func_ov022_020882f8(); i++) {
                pEntry = func_01fffde0(i);
                if ((*(unsigned long long *)pEntry & 0x800) != 0) {
                    continue;
                }

                if (func_ov002_0207b134(pElement, pEntry) != 0) {
                    *(unsigned long long *)pEntry |= 0x800;

                    if ((*(u8 *)(pOwner + 0x88) & (1 << i)) == 0) {
                        nClaimed = 0;
                        for (j = 0; j < func_ov022_020882f8(); j++) {
                            if ((*(u8 *)(pOwner + 0x88) & (1 << j)) != 0) {
                                nClaimed++;
                            }
                        }

                        nDist = (int)(((long long)func_ov002_0206e6d0()
                                       * 0x14000 + 0x800) >> 12);
                        func_ov002_0206bbb8(
                            i, 7,
                            (FX_Mul(data_ov002_0207e6fc[nClaimed], nDist)
                             + 0xfff) >> 12);

                        *(u8 *)(pOwner + 0x88) |= 1 << i;
                    }
                } else {
                    bAllInRange = 0;
                }
            }

            if (bAllInRange) {
                aStart[0] = 1;
                if (func_ov002_020766e0(pElement, aStart, 4) != 0) {
                    *(u8 *)(pElement + 0x1b6) = 1;
                }
            }
        }
        break;

    case 2:
        if (func_ov002_0206b7a4() == 0) {
            if (func_02030788() == 0) {
                func_ov002_0206d928(0);
            }
            *(u8 *)(pElement + 0x1b6) = 3;
            return func_ov002_0207cea4;
        }
        break;
    }

    for (i = 0; i < func_ov022_020882f8(); i++) {
        if ((*(u8 *)(pOwner + 0x88) & (0x10 << i)) == 0
            && (*(u8 *)(pOwner + 0x88) & (1 << i)) != 0) {
            aMsg[0] = 2;
            if (func_ov002_0206b758() != 0) {
                nSlot = func_ov002_02072754(
                    func_ov022_02088474(func_01fffe14()));
            } else {
                nSlot = -1;
            }
            *(short *)(aMsg + 4) = (short)nSlot;
            if (func_ov002_020766e0(pElement, aMsg, 6) != 0) {
                *(u8 *)(pOwner + 0x88) |= 0x10 << i;
            }
        }
    }

    return 0;
}
