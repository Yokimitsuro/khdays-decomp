/* ov022: the local player's command-input dispatcher.
 *
 * Reached from the per-frame actor tick once the actor is confirmed to belong
 * to the local player. It first accumulates a suppression flag from four
 * independent tests and, if any fires, blanks the two-byte menu state and
 * leaves. Otherwise it builds the 15-slot command mask -- optionally split
 * across the two screens -- pushes the mask and the target selection to the
 * HUD, walks the command menu from the button globals, and finally records the
 * chosen command kind and its arguments in the actor.
 *
 * Both 64-bit flag words are read here: the one at 0x00 and the one at 0x464.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Equip {
    u8 pad00[0x17];
    u8 nKind;                    /* 0x17 */
};

struct Actor {
    unsigned long long nFlags;   /* 0x000 */
    u8 pad008[1];
    u8 nId;                      /* 0x009 */
    u8 pad00a[8];
    u16 nHp;                     /* 0x012 */
    u8 pad014[0x10];
    u32 nField24;                /* 0x024 */
    u8 pad028[0x43c];
    unsigned long long nFlags2;  /* 0x464 */
    u8 pad46c[0x64];
    signed char nCommandKind;    /* 0x4d0 */
    u8 pad4d1[1];
    u16 nCmdArg;                 /* 0x4d2 */
    u16 nCmdArg2;                /* 0x4d4 */
    u8 pad4d6[0x12];
    u8 bHudFlag : 1;             /* 0x4e8 bit 0 */
    u8 bMenuFlag : 1;            /* bit 1 */
    u8 nPad4e8 : 1;
    u8 bIdleFlag : 1;            /* bit 3 */
    u8 nRest4e8 : 4;
    u8 pad4e9[0xf];
    struct Equip *pEquip;        /* 0x4f8 */
    u8 pad4fc[0x1d8c];
    short slotMask;              /* 0x2288 */
    u8 pad228a[0x6e];
    u8 stateBlk;                 /* 0x22f8 */
    u8 pad22f9[0x7bf];
    u8 nMenuState;               /* 0x2ab8 */
};

struct ScreenCfg {
    u8 pad00[4];
    u16 nSplit;                  /* 0x04 */
};

extern u8 data_0204c240;
extern struct ScreenCfg data_0204c254;
extern u16 data_0204c18c;
extern u16 data_0204c190;

extern char *func_ov022_02088d04(void);
extern int func_ov022_020ab350(struct Actor *pActor);
extern int func_ov002_0206b7a4(void);
extern int func_02030788(void);
extern int func_020208e0(void);
extern int func_ov022_0209029c(short *pMask, int nSlot);
extern int func_020357f4(u8 nId, int nSlot);
extern void func_ov002_0205dcd4(u8 nSlot, u8 nKind);
extern int func_02023588(int nFlag);
extern int func_ov002_0206b84c(void);
extern int func_ov022_02095450(u8 *pBlk);
extern void func_ov002_0205dc4c(int nMask);
extern void func_ov002_0205e178(int bOn);
extern void func_ov002_0205e124(int nSlot, int nOn);
extern void func_ov002_0205ddcc(int nTarget, int nArg);
extern int func_ov022_020ad1d0(struct Actor *pActor);
extern int func_ov022_02095524(u8 *pBlk);
extern int func_ov002_02076c24(struct Equip *pEquip, u8 nId);
extern int func_ov022_0209fc78(struct Actor *pActor, int nSlot);
extern int func_ov022_0208868c(void);
extern int func_020235d0(int nFlag, int nWhich);
extern int func_ov002_020573cc(void);
extern void func_ov002_02056e04(int bOn);
extern void func_ov002_02056e38(int nCommand);
extern int func_ov002_0206e770(int nWhich);
extern void func_ov002_02056d48(void);
extern void func_ov002_02056fa0(void);
extern int func_ov002_02056d90(int nWhich);
extern void func_ov002_02056cc8(void);
extern int func_ov022_02083f0c(void);
extern int func_ov002_0204cb40(int nSlot);
extern int func_ov022_02088cdc(void);
extern void func_ov002_02056d08(void);
extern void func_ov002_0205d900(void);
extern void func_ov002_0205d810(void);
extern int func_ov002_02056d78(void);
extern u16 func_ov002_0205dc2c(void);
extern u16 func_ov002_0205dfe8(void);
extern u16 func_ov002_0205e1b8(void);
extern u16 func_ov002_0205e1d4(void);
extern int func_ov002_0205d450(void);
extern int func_ov002_0205d464(void);

void func_ov022_020a2978(struct Actor *pActor)
{
    char *pMenu;
    int bCommandChosen;
    int bSuppress;
    int bLock;
    int bMenuActive;
    int bAllySel;
    int i;
    int uMask;
    int nArg;
    int nAim;
    int bBtn;
    int bNoRepeat;
    int nBtn;
    int nCmd;
    int nGlobal;
    int bOk;

    pMenu = func_ov022_02088d04();
    bCommandChosen = 0;
    bSuppress = 0;
    bLock = 0;
    bMenuActive = 0;
    bAllySel = 0;

    if (func_ov022_020ab350(pActor) != 0 || func_ov002_0206b7a4() != 0) {
        bSuppress = 1;
    }
    if ((pActor->nFlags2 & (1ULL << 29)) != 0
        || (pActor->nFlags & (1ULL << 10)) != 0
        || (pActor->nFlags & (1ULL << 45)) != 0) {
        bSuppress = 1;
    }
    if (func_02030788() == 0 && (data_0204c240 & 4) != 0
        && func_020208e0() == 2) {
        bSuppress = 1;
    }
    if (pActor->nHp == 0) {
        bSuppress = 1;
    }
    if (bSuppress != 0) {
        pMenu[0] = 0;
        pMenu[1] = 0;
        return;
    }

    if (pActor->nMenuState == 2 || pActor->nMenuState == 3) {
        bLock = 1;
    }
    if ((pActor->nFlags & (1ULL << 13)) != 0) {
        bLock = 1;
    }
    if ((pActor->nFlags & (1ULL << 11)) != 0
        || (pActor->nFlags2 & (1ULL << 38)) != 0) {
        pActor->nFlags |= (1ULL << 11);
        bLock = 1;
    }

    uMask = 0;
    for (i = 0; i < 15; i++) {
        if (func_ov022_0209029c(&pActor->slotMask, i) != 0) {
            func_ov002_0205dcd4((u8)i, (u8)func_020357f4(pActor->nId, i));
            if ((data_0204c240 & 2) == 0
                || (((data_0204c254.nSplit & 1) == 0 || i >= 12)
                    && ((data_0204c254.nSplit & 2) == 0 || i < 12))) {
                uMask = (u16)(uMask | (1 << i));
            }
        }
    }
    if (func_02023588(0x20e0) != 0) {
        uMask = 0;
    }
    if (func_ov002_0206b84c() == 0x6c && (data_0204c240 & 4) == 0) {
        uMask = 0;
    }
    if (pActor->nMenuState == 6) {
        uMask = 0;
    }
    if (bLock != 0 || func_ov022_02095450(&pActor->stateBlk) != 0) {
        uMask = 0;
    }
    func_ov002_0205dc4c(uMask);

    if (bLock != 0 || func_ov022_02095450(&pActor->stateBlk) != 0
        || (pActor->nFlags & (1ULL << 26)) != 0) {
        func_ov002_0205e178(0);
    } else {
        func_ov002_0205e178(1);
        if ((data_0204c240 & 2) != 0 && (data_0204c254.nSplit & 4) != 0) {
            for (i = 2; i <= 11; i++) {
                func_ov002_0205e124(i, 0);
            }
        }
    }

    if (bLock != 0) {
        func_ov002_0205ddcc(-1, 0);
    } else {
        nAim = func_ov022_020ad1d0(pActor);
        if (nAim != -1
            && (pActor->nFlags2 & (1ULL << 16)) == 0
            && func_ov022_02095524(&pActor->stateBlk) == 0) {
            nArg = func_ov002_02076c24(pActor->pEquip, pActor->nId);
            if (pActor->pEquip->nKind != 0) {
                if ((pActor->nField24 & 4) == 0) {
                    if ((func_ov022_020ad1d0(pActor) & 0x80) == 0) {
                        nArg = 0;
                    }
                } else if ((pActor->nFlags & (1ULL << 36)) != 0
                           && (pActor->nFlags2 & (1ULL << 7)) != 0) {
                    nArg = 0;
                }
            }
            if (pActor->pEquip->nKind == 0) {
                bAllySel = 1;
            }
            func_ov002_0205ddcc(func_ov022_020ad1d0(pActor) & 0xf, nArg);
        } else {
            bAllySel = 1;
            if (func_ov022_0209fc78(pActor, -1) == 0) {
                bAllySel = 0;
            }
            func_ov002_0205ddcc(0, bAllySel);
        }
    }

    if (func_ov022_020ab350(pActor) == 0
        && func_ov022_0208868c() == 0 && bLock == 0) {
        bBtn = 0;
        if (func_020235d0(0x37c4, 1) == 0) {
            if ((data_0204c18c & 0x200) != 0) {
                bBtn = 1;
            }
        } else if ((data_0204c18c & 0x100) != 0
                   && (data_0204c18c & 0x200) != 0) {
            bBtn = 1;
        }
        if (bBtn != 0 && func_ov002_020573cc() == 0
            && (pActor->nFlags2 & (1ULL << 29)) == 0
            && func_ov022_02095450(&pActor->stateBlk) == 0) {
            bMenuActive = 1;
        }
        func_ov002_02056e04(bMenuActive);
        if (bMenuActive != 0) {
            nCmd = -1;
            nBtn = data_0204c190;
            if ((nBtn & 1) != 0) {
                nCmd = 0;
            }
            if ((nBtn & 2) != 0) {
                nCmd = 3;
            }
            if ((nBtn & 0x800) != 0) {
                nCmd = 2;
            }
            if ((nBtn & 0x400) != 0) {
                nCmd = 1;
            }
            if (nCmd < 0) {
                bMenuActive = 0;
            } else {
                func_ov002_02056e38(nCmd);
                bCommandChosen = 1;
            }
        } else {
            bNoRepeat = 1;
            if (func_ov002_0206e770(bNoRepeat) != 0) {
                bNoRepeat = 0;
            }
            if ((data_0204c190 & 1) != 0) {
                bCommandChosen = 1;
                func_ov002_02056d48();
                if (bNoRepeat != 0) {
                    func_ov002_02056fa0();
                }
            } else if ((data_0204c190 & 2) != 0) {
                pActor->bHudFlag = (u8)func_ov002_02056d90(1);
                if (bNoRepeat != 0) {
                    func_ov002_02056fa0();
                }
            }
            if ((data_0204c190 & 0x800) != 0 && bNoRepeat != 0) {
                func_ov002_02056fa0();
            }
            if (func_020235d0(0x37c6, 1) != 0) {
                if ((data_0204c190 & 0x400) != 0
                    && func_ov002_020573cc() == 0 && bCommandChosen == 0) {
                    func_ov002_02056cc8();
                }
            } else {
                nGlobal = func_ov022_02083f0c();
                bOk = 1;
                if ((data_0204c190 & 0x400) != 0
                    && func_ov002_020573cc() == 0 && bCommandChosen == 0) {
                    pMenu[0] = 1;
                    pMenu[1] = 1;
                }
                if ((data_0204c18c & 0x400) != 0) {
                    if (nGlobal != -1 && func_ov002_0204cb40(nGlobal) != 0) {
                        bOk = 0;
                    }
                    if (pMenu[1] == 1) {
                        if ((data_0204c18c & 0xf0) == 0) {
                            pMenu[1] = 2;
                        }
                    } else if (pMenu[1] == 2 && bOk != 0) {
                        if ((func_ov022_02088cdc() & 0x80) != 0) {
                            pMenu[0] = 0;
                            func_ov002_02056cc8();
                        } else if ((func_ov022_02088cdc() & 0x40) != 0) {
                            pMenu[0] = 0;
                            func_ov002_02056d08();
                        } else if ((data_0204c190 & 0x20) != 0) {
                            pMenu[0] = 0;
                            func_ov002_0205d900();
                        } else if ((data_0204c190 & 0x10) != 0) {
                            pMenu[0] = 0;
                            func_ov002_0205d810();
                        }
                    }
                } else {
                    pMenu[1] = 0;
                    if (pMenu[0] > 0) {
                        pMenu[0] = 0;
                        func_ov002_02056cc8();
                    }
                }
            }
        }
    }

    if (bCommandChosen != 0) {
        pActor->nCommandKind = (signed char)func_ov002_02056d78();
        if (func_ov002_020573cc() != 0 && pActor->nCommandKind != 9) {
            pActor->nCommandKind = 7;
        }
        switch (pActor->nCommandKind) {
        case 8:
            pActor->nCmdArg = func_ov002_0205dc2c();
            break;
        case 11:
            pActor->nCmdArg = func_ov002_0205dfe8();
            break;
        case 12:
        case 13:
            pActor->nCmdArg = func_ov002_0205e1b8();
            pActor->nCmdArg2 = func_ov002_0205e1d4();
            break;
        default:
            pActor->nCmdArg = 0;
            break;
        }
        pActor->bMenuFlag = (u8)bMenuActive;
    }
    if (func_ov002_0205d450() == 0 && func_ov002_0205d464() == 0
        && bAllySel != 0) {
        pActor->bIdleFlag = 1;
        return;
    }
    pActor->bIdleFlag = 0;
}
