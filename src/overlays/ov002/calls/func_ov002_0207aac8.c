typedef unsigned short u16;

extern int func_ov002_0206b758(void);
extern int func_ov002_0207a90c(char *pEntry);
extern unsigned short func_01fffe14(void);
extern void *func_01fffde0(unsigned int nIndex);
extern void func_ov022_020ad2e4(void *pEntry, int nMode);
extern void func_020235e8(int nField, int nKind, int nValue);
extern unsigned int func_020235d0(int nField, int nKind);
extern int func_02030788(void);
extern int func_02030670(void);
extern int func_ov002_0206b88c(int bOn);
extern void func_ov002_0206b910(char *pName, void *pText);
extern void func_ov002_0206b998(void *pfnDone, char *pEntry);
extern void func_ov002_0206b9b4(unsigned char nBits);
extern int func_ov002_0206b9cc(void);
extern void func_ov002_0206b97c(void);
extern int func_ov002_0206b78c(void);
extern int func_ov022_02083f0c(void);
extern int func_ov022_02083f5c(void);
extern void func_ov022_02086818(int nHandle, int nMode);
extern void func_ov002_0204cee0(int nHandle, int nMode);
extern void func_ov002_0204cb70(int nHandle, int nMode, void *pExtra);
extern void *func_ov022_020881f8(int nIndex);
extern int func_ov022_020882f8(void);
extern int func_01ff8e94(void *pA, void *pB);
extern void func_ov022_020acbf0(void *pEntry);
extern void func_ov002_0207aa94(char *pEntry);
extern int func_ov002_020766e0(void *pEntry, void *pReq, int nKind);
extern void func_ov022_020888ec(int nIndex, int bOn);
extern void func_ov002_020767bc(int arg0, int arg1);
extern void func_ov002_02076bd8(char *pEntry, int nMode);

/* Run one step of a spare entry's state machine.
 *
 * Whoever is standing in the trigger radius gets nudged first. Then the phase
 * decides: phase 2 is the hand-over, where the owner's game-state field is
 * published and, for the player who owns the entry, either the plain
 * announcement or the full line - which streams the text, hands over the done
 * callback, adjusts the session flags and, in the one phase word that asks for
 * it, pushes every distant entry away. Phases 4 and 5 queue a record and drop
 * back to phase 1, and phase 6 tears the entry down and writes its state back.
 */
int func_ov002_0207aac8(char *pEntry)
{
    char *pOwner;
    int nHandle;
    int nOther;
    int i;
    void *pSelf;
    void *pEntryI;
    unsigned int nState;

    pOwner = *(char **)(pEntry + 8);

    if (func_ov002_0206b758() != 0 && func_ov002_0207a90c(pEntry) != 0) {
        func_ov022_020ad2e4(func_01fffde0(func_01fffe14()), 1);
    }

    switch (*(unsigned char *)(pEntry + 0x2c)) {
    case 2:
        func_020235e8(0x20dd, 3, *(unsigned char *)(pEntry + 0x3f));

        if (*(unsigned char *)(pEntry + 0x3f) == func_01fffe14()) {
            if (*(unsigned char *)(pOwner + 0x5a) != 0) {
                func_020235e8(*(u16 *)(pOwner + 0x58),
                              *(unsigned char *)(pOwner + 0x5a),
                              *(unsigned char *)(pEntry + 0x2d));
            }

            if (*(signed char *)(pEntry + 0x37) != 0) {
                if (func_02030788() != 0) {
                    func_ov002_0206b88c(1);
                }

                func_ov002_0206b910(*(signed char *)(pEntry + 0x2f) != 0
                                        ? pEntry + 0x2f : 0,
                                    pEntry + 0x37);
                func_ov002_0206b998(func_ov002_0207aa94, pEntry);

                if (func_02030670() != 0) {
                    func_ov002_0206b9b4(0);
                } else {
                    func_ov002_0206b9b4(
                        (unsigned char)(func_ov002_0206b9cc() & ~0xa));
                }
                func_ov002_0206b97c();

                if (func_ov002_0206b78c() == 1) {
                    nHandle = func_ov022_02083f0c();
                    func_ov022_02086818(func_ov022_02083f5c(), 0);
                    func_ov002_0204cee0(nHandle, 1);

                    if ((*(signed char *)(pEntry + 0x40) & 0x20) != 0) {
                        func_ov002_0204cb70(nHandle, 1, 0);

                        if (func_02030670() == 0) {
                            pSelf = func_ov022_020881f8(func_01fffe14());
                            for (i = 0; i < func_ov022_020882f8(); i++) {
                                pEntryI = func_01fffde0(i);
                                if ((*(unsigned long long *)pEntryI & 0x10000)
                                    != 0) {
                                    nOther = func_01ff8e94(
                                        pSelf, func_ov022_020881f8(i));
                                    if (nOther >= 0x3000) {
                                        func_ov022_020acbf0(pEntryI);
                                    }
                                }
                            }
                        }
                    }
                }

                *(unsigned char *)(pEntry + 0x2c) = 3;
            } else {
                func_ov002_0207aa94(pEntry);
                func_ov002_0206b88c(0);
            }
        } else {
            *(unsigned char *)(pEntry + 0x17) = 0;
            func_ov002_0206b88c(0);
        }
        break;

    case 4:
        if (func_02030788() == 0) {
            unsigned char aReq[6];

            aReq[0] = 3;
            aReq[4] = *(unsigned char *)(pEntry + 0x3f);
            if (func_ov002_020766e0(pEntry, aReq, 6) == 0) {
                return 0;
            }
        } else {
            unsigned char aReq[6];

            aReq[0] = 2;
            aReq[4] = *(unsigned char *)(pEntry + 0x3f);
            if (func_ov002_020766e0(pEntry, aReq, 6) == 0) {
                return 0;
            }
        }

        *(unsigned char *)(pEntry + 0x17) = *(signed char *)(pEntry + 0x2e);
        if (func_ov002_0206b758() != 0) {
            func_ov022_020888ec(*(unsigned char *)(pEntry + 0x3f), 0);
        }
        *(unsigned char *)(pEntry + 0x2c) = 1;
        break;

    case 5:
        {
            unsigned char aReq[6];

            aReq[0] = 3;
            aReq[4] = *(unsigned char *)(pEntry + 0x3f);
            if (func_ov002_020766e0(pEntry, aReq, 6) != 0) {
                *(unsigned char *)(pEntry + 0x2c) = 1;
            }
        }
        break;

    case 6:
        *(unsigned char *)(pEntry + 0x17) = *(signed char *)(pEntry + 0x2e);
        func_ov002_020767bc(0, *(unsigned char *)(pEntry + 0x3f));
        *(unsigned char *)(pEntry + 0x2c) = 0;

        if ((*(signed char *)(pEntry + 0x40) & 0x10) == 0
            && (*(signed char *)(pEntry + 0x40) & 0xf) == 0) {
            *(u16 *)(pEntry + 0x12) &= ~8;
            func_ov002_02076bd8(pEntry, 0);
        }

        if (*(signed char *)(pEntry + 0x37) != 0) {
            func_ov022_020888ec(*(unsigned char *)(pEntry + 0x3f), 0);

            if (func_ov002_0206b78c() == 1) {
                nHandle = func_ov022_02083f0c();
                nOther = func_ov022_02083f5c();

                if ((*(signed char *)(pEntry + 0x40) & 0x20) != 0) {
                    func_ov002_0204cb70(nHandle, 0, 0);
                }
                func_ov002_0204cee0(nHandle, 0);
                func_ov022_02086818(nOther, 1);
            }
        }

        nState = func_020235d0(*(u16 *)(pEntry + 0x14),
                               *(unsigned char *)(pEntry + 0x16));
        func_020235e8(*(u16 *)(pEntry + 0x14),
                      *(unsigned char *)(pEntry + 0x16),
                      (u16)((nState & ~0xfffe) | 2));
        break;
    }

    return 0;
}
