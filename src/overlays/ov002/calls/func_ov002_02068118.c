/*
 * Runs one frame of the multiplayer session screen and hands back the next
 * state, or nothing to stay where it is.
 *
 * While this machine owns the session and its countdown is still running, the
 * countdown is stepped once a frame and fires its expiry hook when it reaches
 * zero. The peer mask is then rebuilt from scratch: bit four always, plus one
 * bit per peer that answers the poll.
 *
 * From there the frame is a cascade of gates, each of which can hand back a
 * different state: the cancel and back flags, the two join requests, the give
 * up path, a pending command to retire, the queued slot request, and finally
 * the state seven gate that leaves for the shop when the right combination of
 * global flags is set. If none of them fires, the screen's own per-frame
 * handler runs and can ask for a state change itself.
 *
 * Four things here are load-bearing rather than style.
 *
 * The peer-mask update in the loop takes no cast. Written with one the compiler
 * masks to a byte explicitly and loses the predication the original uses.
 *
 * The two places that clear bit four and set bit five are written as two
 * compound assignments, the clear then the set. Written as one assignment the
 * compiler updates the loaded value in place instead of computing the clear
 * into a register of its own.
 *
 * The silencer branch tests for the flag being clear, not set, so its two arms
 * come out in the original's order.
 *
 * The pending command is retired by a helper that takes both the command's kind
 * byte and the command itself. That second argument is why the original keeps
 * the pointer in its own register rather than reading the byte over it.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct Ov002SessionLink {
    char pad000[2];
    s16 nSubState;
    char pad004[4];
    int nFieldA;
    int nFieldB;
    char pad010[8];
    int nSavedSubState;
} Ov002SessionLink;

typedef struct Ov002SessionPeer {
    char pad000[0xc];
    s8 nReady;
} Ov002SessionPeer;

typedef struct Ov002SessionScreen {
    char pad0000[0x8b40];
    s8 nPending;
    u8 nSlotByte;
    char pad8b42[0x16];
    int nState;
    char pad8b5c[4];
    int nSlotIndex;
    int nFlags;
    u8 nMask;
    char pad8b69[0x27];
    void *(*pHandler)(void);
    char pad8b94[0x14];
    Ov002SessionLink link;
    char pad8bc4[0x1a8];
    Ov002SessionPeer peer;
    char pad8d7d[0x1f];
    s16 nCountdown;
    char pad8d9a[0x22];
    u8 *pCommand;
} Ov002SessionScreen;

extern u8 data_0204be04;
extern u8 data_0204c240;
extern u16 data_0204c190;
extern u16 data_0204c18c;

extern Ov002SessionScreen *NNSi_FndGetCurrentRootHeap(void);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern int func_02030788(void);
extern int func_02030694(void);
extern int func_020235d0(int a, int b);
extern void func_020208d0(int a);
extern void func_02020878(int a);
extern void func_02033b78(int a, int b);
extern int func_01fffe14(void);
extern int *func_01fffde0(int a);
extern int func_ov002_0206b7a4(void);
extern int func_ov002_020573cc(void);
extern void func_ov002_0206a894(void);
extern void func_ov002_0206bfc8(void);
extern int func_ov002_0206b758(void);
extern int func_ov022_020882f8(void);
extern int func_ov002_02074314(int a, int b);
extern int func_ov002_0206a91c(int a);
extern int func_ov002_0206a804(void);
extern void func_ov002_0206d928(int a);
extern void func_ov002_0206dec4(void);
extern int func_ov002_0206fb84(int nKind, const u8 *pCommand);
extern void func_ov002_0206a11c(void);
extern void func_ov002_0206f514(int a);
extern void func_ov002_0206aae4(int a, int b);
extern void func_ov002_0206b88c(int a);
extern void func_ov002_0206ed7c(void);
extern int func_ov002_0206eb40(void);
extern int func_ov002_02069554(void);
extern int func_ov002_0206eb64(int a);
extern int func_ov002_0206ebd4(void);
extern void func_ov002_02056fa0(void);
extern int func_ov022_02088648(void);
extern int func_ov022_020886d0(int a);
extern int func_ov002_020767d4(u16 a);
extern void func_ov002_0206eb20(void);
extern void func_ov002_02068d54(void);
extern void func_ov002_02068c0c(void);
extern void func_ov002_02068a20(void);

void *func_ov002_02068118(void)
{
    Ov002SessionScreen *pSess;
    Ov002SessionLink *pLink;
    void *pNext;
    Ov002SessionPeer *pPeer;
    int i;
    int nSlot;

    pNext = 0;
    pSess = NNSi_FndGetCurrentRootHeap();
    pLink = &pSess->link;
    pPeer = &pSess->peer;
    if (data_0204be04 != 0) {
        return pNext;
    }

    if (func_02030788() == 0 && pSess->nCountdown >= 0
        && func_ov002_0206b7a4() == 0 && func_ov002_020573cc() == 0) {
        pSess->nCountdown = (s16)(pSess->nCountdown - 1);
        if (pSess->nCountdown <= 0) {
            func_ov002_0206a894();
            pSess->nCountdown = -1;
        }
    }

    func_ov002_0206bfc8();
    pSess->nMask = 0x10;
    if (func_ov002_0206b758() != 0) {
        i = 0;
        if (func_ov022_020882f8() > 0) {
            do {
                if (func_ov002_02074314(i, -0x1000) != 0) {
                    pSess->nMask |= 1 << i;
                }
                i++;
            } while (i < func_ov022_020882f8());
        }
    }

    if (pSess->nState == 7 || pSess->nState == 1 || pSess->nState == 5) {
        if ((pSess->nFlags & 0x40) != 0) {
            pLink->nFieldA = 0;
            pLink->nFieldB = 0;
            return func_ov002_02068d54;
        }
        if ((pSess->nFlags & 4) != 0) {
            pLink->nFieldA = 0;
            if ((data_0204c240 & 4) != 0) {
                pLink->nFieldB = -1;
                pLink->nSubState = -3;
            } else {
                pLink->nFieldB = 0;
            }
            return func_ov002_02068d54;
        }
        if ((pSess->nFlags & 0x22) != 0) {
            return 0;
        }
        if (func_02030694() != 0) {
            if ((pSess->nFlags & 0x10) != 0) {
                if (func_ov002_0206a91c(1) != 0) {
                    pSess->nFlags = (pSess->nFlags & ~0x10) | 0x20;
                    return 0;
                }
            } else if ((pSess->nFlags & 1) != 0) {
                if (func_ov002_0206a91c(0) != 0) {
                    pSess->nFlags = (pSess->nFlags & ~1) | 2;
                    return 0;
                }
            }
        }
        if (func_ov002_0206a804() != 0 && func_02030788() == 0) {
            if ((data_0204c240 & 4) != 0) {
                func_ov002_0206d928(0);
            }
            return 0;
        }
    }

    func_ov002_0206dec4();
    if (pSess->pCommand != 0
        && func_ov002_0206fb84(pSess->pCommand[0], pSess->pCommand) != 0xffff) {
        NNSi_FndFreeFromDefaultHeap(pSess->pCommand);
        pSess->pCommand = 0;
    }
    func_ov002_0206a11c();

    if (pSess->nState == 7 || pSess->nState == 1 || pSess->nState == 5) {
        if (pSess->nPending != 0) {
            pSess->nPending = 0;
            if ((data_0204c240 & 4) == 0) {
                func_ov002_0206f514(1);
            } else {
                func_020208d0(0);
            }
            func_02020878(0);
            func_ov002_0206aae4(1, pSess->nSlotByte);
            pSess->nSlotByte = 0xff;
            pSess->nMask &= ~0x10;
            pSess->nMask |= 0x20;
            func_ov002_0206b88c(0);
            return func_ov002_02068c0c;
        }
        if (pPeer->nReady >= 0) {
            pSess->nFlags &= ~0x100;
            if ((data_0204c240 & 4) != 0) {
                func_020208d0(0);
            }
            func_ov002_0206aae4(1, 0xff);
            func_ov002_0206ed7c();
            return func_ov002_02068d54;
        }
    }

    nSlot = func_ov002_0206eb40();
    if (nSlot != -1 && func_ov002_02069554() != 0) {
        if (func_02030694() != 0) {
            if (func_ov002_0206eb64(nSlot) == 0) {
                return 0;
            }
            if ((data_0204c240 & 4) != 0) {
                func_020208d0(0);
            }
            func_02020878(0);
            if ((data_0204c240 & 4) == 0) {
                func_ov002_0206f514(1);
            }
        } else {
            if (func_ov002_0206ebd4() == 0) {
                return 0;
            }
        }
        pSess->nMask &= ~0x10;
        pSess->nMask |= 0x20;
        pSess->nSlotIndex = nSlot;
        func_ov002_02056fa0();
        return func_ov002_02068a20;
    }

    if (pSess->nState == 7
        && ((data_0204c190 & 8) != 0
            || ((data_0204c190 & 0x800) != 0 && (data_0204c18c & 0x200) == 0
                && (u32)func_020235d0(0, 9) >= 0xb))
        && func_ov022_02088648() == 0 && func_ov002_0206b7a4() == 0
        && func_ov022_020886d0(0) == 0 && pSess->nPending == 0) {
        if ((func_01fffde0(func_01fffe14())[9] & 4) != 0) {
            if (func_ov002_020767d4((u16)func_01fffe14()) == 0) {
                pLink->nSavedSubState = pLink->nSubState;
                pLink->nSubState = (data_0204c190 & 8) != 0 ? -2 : -7;
                func_ov002_0206f514(1);
                func_ov002_0206ed7c();
                func_ov002_0206eb20();
                func_ov002_0206aae4(1, 0xff);
                func_02033b78(0, 2);
                pSess->nMask &= ~0x10;
                return func_ov002_02068d54;
            }
        }
    }

    if (pSess->pHandler != 0) {
        if (pSess->pHandler() != 0) {
            func_ov002_0206ed7c();
            pSess->nMask &= ~0x10;
            pNext = func_ov002_02068d54;
        }
    }
    return pNext;
}
