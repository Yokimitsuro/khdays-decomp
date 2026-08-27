/*
 * Answers whether the multiplayer session may honour a queued slot request.
 *
 * The answer is no while the story flag is set, while an installed veto hook
 * says no, while either leave flag is raised, and while a slot is held in a
 * phase that is not one of the three that tolerate a swap. It is also no if
 * any peer entry carries the busy flag or has work of its own outstanding.
 *
 * Past all that, the link itself has to be idle unless the boot-mode pair says
 * otherwise, and when the tally flag is set the request also has to fit the
 * budget: the leading assigned tally ids plus the bits of the id mask must not
 * exceed the configured allowance.
 *
 * Three things here are load-bearing rather than style.
 *
 * A peer entry's first eight bytes are one 64-bit flag word. The original
 * masks the low half with the bit and the high half with zero and then
 * compares the pair against zero, which is what a 64-bit test lowers to;
 * written as a plain int test the function comes out four instructions short.
 *
 * The three link checks are one condition joined to the boot-mode test rather
 * than three statements, so all of them reach a single shared `return 0` the
 * way the original does. Written as separate statements the compiler
 * predicates each exit into its own `pop`.
 *
 * The session block is reached through its own pointer, which is what gives
 * the phase load its base register instead of folding the offset onto the
 * context.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SessionSlot {
    int nHandle;
    char pad004[0x28];
} Ov002SessionSlot;

typedef struct Ov002SessionBlock {
    Ov002SessionSlot aSlots[4];
    char pad0b0[9];
    s8 anTallyIds[5];
    u8 nTallyIdMask;
    char pad0bf[1];
    int nPhase;
} Ov002SessionBlock;

typedef struct Ov002RootContext {
    char pad0000[0x8b64];
    int nFlags;
    char pad8b68[0x34];
    int (*pHook)(void);
    char pad8ba0[0x2c];
    Ov002SessionBlock session;
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern u8 data_0204c240;
extern u8 data_0204c248[];

extern int func_02023588(int nFlagId);
extern int func_ov022_020882f8(void);
extern int *func_01fffde0(int nIndex);
extern int func_ov002_020767d4(u16 nIndex);
extern int func_01fffe14(void);
extern int func_ov022_020886d0(int nIndex);
extern int func_ov022_020882e0(int nIndex);

int func_ov002_02069554(void)
{
    Ov002RootContext *pCtx;
    Ov002SessionBlock *pSession;
    int i;
    int nUsed;

    pCtx = data_ov002_0207fa00;
    if (func_02023588(0x2087) != 0) {
        return 0;
    }
    if (pCtx->pHook != 0 && pCtx->pHook() == 0) {
        return 0;
    }
    if ((pCtx->nFlags & 0x100) != 0) {
        return 0;
    }
    if ((pCtx->nFlags & 0x200) != 0) {
        return 0;
    }
    pSession = &pCtx->session;
    if (pSession->aSlots[0].nHandle != -1 && pSession->nPhase != 5
        && pSession->nPhase != 0 && pSession->nPhase != 2) {
        return 0;
    }

    i = 0;
    if (func_ov022_020882f8() > 0) {
        do {
            if ((*(unsigned long long *)func_01fffde0(i) & 0x800) != 0) {
                return 0;
            }
            if (func_ov002_020767d4((u16)i) != 0) {
                return 0;
            }
            i++;
        } while (i < func_ov022_020882f8());
    }

    if ((data_0204c240 & 0xc) != 4
        && ((func_01fffde0(func_01fffe14())[281] & 0x10000000) != 0
            || func_ov022_020886d0(func_01fffe14()) != 0
            || func_ov022_020882e0(func_01fffe14()) <= 0)) {
        return 0;
    }

    if ((data_0204c240 & 4) != 0) {
        nUsed = 0;
        while (nUsed < 5) {
            if (pCtx->session.anTallyIds[nUsed] < 0) {
                break;
            }
            nUsed++;
        }
        for (i = 0; i < 4; i++) {
            if ((pCtx->session.nTallyIdMask & (1 << i)) != 0) {
                nUsed++;
            }
        }
        if (data_0204c248[3] < nUsed) {
            return 0;
        }
    }
    return 1;
}
