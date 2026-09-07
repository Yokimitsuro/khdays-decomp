/* ov022: set an entity's hit points, clamped to its maximum.
 *
 * Dropping to zero is the interesting path: it plays a death cue that depends
 * on the game mode and on whether the entity is the local player's, and in one
 * mode it refuses the kill outright by forcing the value back to 1.
 *
 * The flag clear at the end is the same 64-bit mask shape as the state-entry
 * handler: clearing bit 37 loads and stores BOTH halves, and the compiler
 * derives the low mask from the high one with add r0, r1, #0x20.
 */
#pragma opt_dead_assignments off

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct Ent {
    unsigned long long nFlags;   /* 0x00 */
    u8 nOwner;                   /* 0x08 */
    u8 nId;                      /* 0x09 */
    u8 pad0a[8];
    u16 nHp;                     /* 0x12 */
    u8 pad14[2];
    u16 nHpMax;                  /* 0x16 */
};

extern u8 data_0204be04;
extern u8 data_0204c240;

extern int func_ov022_02083f5c(void);
extern void func_ov022_0209a68c(u32 *pEnt, int nOn);
extern u32 func_02030788(void);
extern int func_ov002_0206bb7c(u8 nId);
extern void func_02033bb4(int a, int b, int c);
extern void func_02033b24(int a, int nCue);
extern void func_ov022_020a4490(u32 *pEnt, int a, int nCue);
extern void func_ov022_02086638(int nCtx, int nOn);
extern void func_ov002_02056a54(u8 nId, u16 nHp);

void func_ov022_020acc94(u32 *pEnt, int nValue)
{
    struct Ent *pSelf = (struct Ent *)pEnt;
    int nCtx;
    int nMax;

    nCtx = func_ov022_02083f5c();
    if (data_0204be04 != 0) {
        return;
    }
    if (nValue != pSelf->nHp) {
        if (pSelf->nHp == 0 && nValue > 0) {
            func_ov022_0209a68c(pEnt, 0);
        }
        if (pSelf->nHp != 0 && nValue <= 0) {
            if ((data_0204c240 & 4) != 0
                && func_02030788() == 0
                && func_ov002_0206bb7c(pSelf->nId) == 0) {
                nValue = 1;
            }
            if (pSelf->nOwner == func_02030788() && nValue <= 0) {
                if ((data_0204c240 & 4) != 0) {
                    func_02033bb4(0, 8, 0);
                    func_ov022_020a4490(pEnt, 0, 0x2b);
                } else {
                    int nSlot;
                    if ((nSlot = 0, pEnt[0] & 0x10000) != 0) {
                        func_ov022_020a4490(pEnt, nSlot, 0x2a);
                    } else {
                        func_02033bb4(nSlot, 8, 0xa);
                        func_02033b24(0, 0x29);
                    }
                }
                if ((pEnt[0] & 0x10000) == 0) {
                    func_ov022_02086638(nCtx, 1);
                }
            }
        }
        nMax = pSelf->nHpMax;
        if (nValue <= (int)nMax) {
            if (nValue < 0) {
                nValue = 0;
            }
            nMax = nValue;
        }
        pSelf->nHp = (u16)nMax;
        if (pSelf->nHp == pSelf->nHpMax) {
            pSelf->nFlags &= ~(1ULL << 37);
        }
    }
    func_ov002_02056a54(pSelf->nId, pSelf->nHp);
}

#pragma opt_dead_assignments on
