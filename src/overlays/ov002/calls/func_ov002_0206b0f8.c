typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

/* The roster block the overlay keeps at +0x8bcc of its root.  The seats it
   points at are Ov002RosterSlot records: vecBase at +0, nBaseValue at +0xc,
   nSeatId at +0x10, aSeatData at +0x14, vecTarget at +0x34 and nTargetValue
   at +0x40.  They are reached here through a walking byte offset rather than
   an index, which is what keeps the multiply out of the loops. */
typedef struct Ov002RosterBlock {
    void *pInstance;                /* +0x00, -1 until the class is made */
    char *pSeats;                   /* +0x04, four 0x44 byte seats */
    char pad008[0xb0];
    u8 bSeatMask;                   /* +0xb8, low nibble */
} Ov002RosterBlock;

/* What the roster class is instantiated with. */
typedef struct Ov002RosterArgs {
    int aPresent[4];                /* +0x00 */
    int aReady[4];                  /* +0x10 */
    int bIsMode3;                   /* +0x20 */
} Ov002RosterArgs;                  /* 0x24 */

/* The command Ov002_BuildSessionCommand takes for kind 6. */
typedef struct Ov002SessionCmd {
    u8 bPad;                        /* +0x00, never written */
    u8 bSeat;                       /* +0x01 */
    u8 bSeatId;                     /* +0x02 */
    char pad03[1];
    Vec3 vPos;                      /* +0x04 */
    int nBaseValue;                 /* +0x10 */
    char aName[0x10];               /* +0x14 */
} Ov002SessionCmd;                  /* 0x24 */

extern char *data_ov002_0207fa00;
extern u8 data_0204c240;                /* boot-mode flags */
extern u16 data_0204c678[];             /* 0x104 byte records */
extern u8 data_02042a1c;
extern u8 data_0204c4f1;
extern int data_02041dc8;               /* the zero vector */
extern int data_ov022_020b291c;         /* the roster class */

extern void func_020358c0(int a, int b, int c);
extern int func_02023588(int nFlag);
extern void func_020235bc(int nFlag);
extern void func_ov002_0206d384(void);
extern int func_02023930(const void *pClass, void *pArgs);
extern void func_ov022_0208808c(int a);
extern int func_02030670(void);
extern int func_02030788(void);
extern void func_ov002_0206b4bc(int index, int a, int *out, int d, void *buf, int f);
extern int func_02035cac(int a, int b);
extern void func_ov002_0206ba78(int a, int b);
extern void func_ov002_0206d9fc(int a);
extern void func_ov002_0206a2cc(void);
extern int func_ov002_0207285c(int nId);
extern int func_ov002_020726dc(int nId);
extern int func_ov002_02072718(int nId);
extern int func_01fff974(void);
extern int func_ov022_020882f8(void);
extern void func_0201f924(char *pDst, const char *pSrc);
extern int func_ov002_0206fb84(int nKind, void *pCmd);

/* Brings the roster up and tells the caller whether it is settled.
 *
 * The first call makes the roster class, after patching the four mode words
 * for the two special stages and for modes 6 and 7. Each of the four seats
 * gets a present flag, which only counts from the second seat on and only up
 * to the live count, and a ready flag that modes 4 and 5 force on. Mode 8
 * additionally rewrites the fourth word of every record from a quarter of its
 * own seventh word.
 *
 * After that, a live session with a non-zero local index only has to agree on
 * the seat mask. Otherwise the roster is walked once per phase: the first pass
 * writes every seat's marker, and later passes push one session command per
 * seat until one is refused. Returning non-zero means the roster is settled,
 * and that also resets the phase.
 */
int func_ov002_0206b0f8(int nMode)
{
    Ov002RosterArgs args;
    Ov002SessionCmd cmd;
    u16 aTmp[8];
    char *pRoot;
    Ov002RosterBlock *pRoster;
    char *pEntry;
    char *pBlock;
    int i;
    int *pArg;
    u16 *pRec;
    u16 *pRec2;
    int nResult;
    int nCount;
    int nDelta;
    int nOff;
    int nId;
    int nSeat;
    int bDone;
    int nPresent;
    int nOff2;
    int j;
    s8 *pCounter;

    pRoot = data_ov002_0207fa00;
    pRoster = (Ov002RosterBlock *)(pRoot + 0x8bcc);
    nResult = 1;

    if ((int)pRoster->pInstance == -1) {
        if ((data_0204c240 & 4) == 0) {
            aTmp[4] = data_0204c678[0];
            aTmp[5] = data_0204c678[1];
            aTmp[6] = data_0204c678[2];
            aTmp[7] = data_0204c678[3];

            if (*(s16 *)(pRoot + 0x8ba8) == 0x6c) {
                ((u8 *)aTmp)[0xc] = 0x2e;
            } else if (*(s16 *)(pRoot + 0x8ba8) == 0x3ed) {
                ((u8 *)aTmp)[0xc] = 0x30;
            } else {
                switch (nMode) {
                case 6:
                    ((u8 *)aTmp)[0xb] = 0x14;
                    ((u8 *)aTmp)[0xc] = 0x2f;
                    break;
                case 7:
                    ((u8 *)aTmp)[0xb] = 0x13;
                    ((u8 *)aTmp)[0xc] = (u8)nResult;
                    break;
                }
            }

            data_0204c678[0] = aTmp[4];
            data_0204c678[1] = aTmp[5];
            data_0204c678[2] = aTmp[6];
            data_0204c678[3] = aTmp[7];

            if (nMode == 7) {
                func_020358c0(0, 0x65, 1);
            } else if (nMode == 6) {
                func_020358c0(0, 0x65, 0);
            }
        }

        nCount = data_02042a1c;
        pRec = data_0204c678;
        i = 0;
        pArg = args.aPresent;
        nDelta = nMode - 4;
        pRec2 = pRec;
        do {
            if (i != 0 && nCount >= i) {
                nPresent = 1;
            } else {
                nPresent = 0;
            }
            pArg[0] = nPresent;

            if ((unsigned int)nDelta <= 1) {
                pArg[4] = 1;
            } else if (nMode == 8) {
                aTmp[0] = pRec2[0];
                aTmp[1] = pRec2[1];
                aTmp[2] = pRec2[2];
                aTmp[3] = pRec2[3];
                aTmp[3] = (u16)(((int)pRec[7] >> 2) - 1);
                pRec[0] = aTmp[0];
                pRec[1] = aTmp[1];
                pRec[2] = aTmp[2];
                pRec[3] = aTmp[3];
                pArg[4] = data_0204c4f1;
            } else {
                pArg[4] = data_0204c4f1;
            }

            args.bIsMode3 = 0;
            i++;
            pArg++;
            pRec += 0x82;
            pRec2 += 0x82;
        } while (i < 4);

        if (nMode == 3) {
            args.bIsMode3 = 1;
        }
        if (func_02023588(0x2088) != 0) {
            func_ov002_0206d384();
        }
        pRoster->pInstance = (void *)func_02023930(&data_ov022_020b291c, &args);
        func_ov022_0208808c(1);
    }

    if (func_02030670() == 0 || func_02030788() == 0) {
        nResult = 0;
        if (*(s8 *)(pRoot + 0x8db6) == 0) {
            if (func_02023588(0x2088) != 0 || nMode == 2) {
                for (i = 0, nOff = 0; i < 4; i++) {
                    pEntry = pRoster->pSeats + nOff;
                    func_ov002_0206b4bc(i, *(int *)(pEntry + 0x10),
                                        (int *)(pEntry + 0x34),
                                        *(int *)(pEntry + 0x40), 0, 1);
                    nOff += 0x44;
                }
                if ((data_0204c240 & 4) == 0) {
                    func_02035cac(1, 1);
                }
                if (func_02023588(0x2088) != 0) {
                    func_020235bc(0x2088);
                }
            } else if (nMode == 0 || nMode == 4 || nMode == 3
                       || (unsigned int)(nMode - 6) <= 2) {
                for (j = 0, nOff2 = 0; j < 4; j++) {
                    pEntry = pRoster->pSeats + nOff2;
                    func_ov002_0206b4bc(j, *(int *)(pEntry + 0x10), (int *)pEntry,
                                        *(int *)(pEntry + 0xc), 0, 0);
                    nOff2 += 0x44;
                }
                func_ov002_0206ba78(0, -1);
            } else if (nMode == 1 || nMode == 5) {
                pBlock = pRoot + 0x8d6c;
                if (*(s8 *)(pBlock + 0xc) >= 0) {
                    for (i = 0; i < 4; i++) {
                        func_ov002_0206b4bc(i, *(s8 *)(pBlock + 0xc),
                                            &data_02041dc8, 0, pBlock, 0);
                    }
                    func_ov002_0206d9fc(2);
                    func_ov002_0206ba78(0, -1);
                } else {
                    for (i = 0, nOff = 0; i < 4; i++) {
                        nId = *(int *)(pRoster->pSeats + nOff + 0x10);
                        if (nId >= 0 && func_ov002_0207285c(nId) < 0) {
                            nSeat = func_ov002_02072718(
                                        func_ov002_020726dc(nId));
                            if (nSeat >= 0) {
                                func_ov002_0207285c(nSeat);
                                *(int *)(pRoster->pSeats + nOff + 0x10) = nSeat;
                            }
                        }
                        nOff += 0x44;
                    }
                }
            }
            func_ov002_0206a2cc();
            *(s8 *)(pRoot + 0x8db6) = (s8)(*(s8 *)(pRoot + 0x8db6) + 1);
        } else {
            if (func_02030670() != 0) {
                bDone = 0;
                if (*(s8 *)(pRoot + 0x8db6) - 1 < func_ov022_020882f8()) {
                    pCounter = (s8 *)(pRoot + 0x8db6);
                    do {
                        pEntry = pRoster->pSeats
                                 + (*(s8 *)(pRoot + 0x8db6) - 1) * 0x44;
                        cmd.bSeat = (u8)(*(s8 *)(pRoot + 0x8db6) - 1);
                        cmd.bSeatId = (u8)*(int *)(pEntry + 0x10);
                        cmd.vPos = *(Vec3 *)pEntry;
                        cmd.nBaseValue = *(int *)(pEntry + 0xc);
                        func_0201f924(cmd.aName, pEntry + 0x14);
                        if (func_ov002_0206fb84(6, &cmd) == 0xffff) {
                            bDone = 1;
                            break;
                        }
                        *pCounter = (s8)(*pCounter + 1);
                    } while (*(s8 *)(pRoot + 0x8db6) - 1
                             < func_ov022_020882f8());
                }
                if (bDone == 0) {
                    nResult = 1;
                }
            } else {
                nResult = 1;
            }
        }
    } else {
        if ((pRoster->bSeatMask & 0xf) != func_01fff974()) {
            nResult = 0;
        } else {
            if (*(s8 *)(pRoot + 0x8d78) >= 0) {
                func_ov002_0206a2cc();
                func_ov002_0206d9fc(2);
            }
            *(u8 *)(pRoot + 0x8c84) &= ~0xf;
        }
    }

    if (nResult != 0) {
        *(u16 *)(pRoot + 0x8db4) = 0xffff;
        *(u8 *)(pRoot + 0x8db6) = 0;
    }
    return nResult;
}
