/* NOT MATCHING -- 262 of 284 bytes, 67 of 71 instructions aligned.
 *
 * Exact size, exact instruction count and exact relocations. The residue is 16
 * bytes over 7 words and nothing else: the ROM materialises the cursor's
 * address at 0xdc, before the three-word copy, so it takes r4, while this
 * source materialises it at 0xe8, straight after the copy, where it takes r2.
 * The three accesses through it differ only in that register. Everything
 * outside 0x78..0x114 is byte identical.
 *
 * The cause is measured, not guessed. On a minimal probe, a function that
 * calls something, binds a global's address, copies three words through a
 * pointer and reads the global back emits exactly the ROM's shape as
 * straight-line code; wrapping the identical statements in any conditional --
 * an if on a field, a switch with one case, a switch with two -- moves the load
 * to the slot after the store. The trigger is the nesting, and this arm is
 * under the mode dispatch. Across all matched ARM sources the only functions
 * that keep an early load under a conditional are four members of one family
 * where the early value is the source base of a second block move; this cursor
 * is a scalar load base, and making it one needs a struct local, which the
 * compiler gives a stack slot.
 *
 * Closed by measurement: the statement grammar of the arm exhaustively by
 * machine over 624 distinct bodies, the dispatch structure, the setup, the
 * mode 0 arm, fourteen declarations of the global and four linkages, eight
 * zero-folding indices, the copy's spelling, named source and destination
 * pointers, the nested sub-struct, qualifiers and aliasing, the caller and the
 * parameter passing convention, the C++ lane, and the compiler's own
 * optimisation pragmas.
 */

/* Ov022_PoolTakeSlotAt -- take a slot from the owner's animation slot pool
 * and place it at a position.
 *
 * The pool hangs at owner+0x20. The caller's position is copied in with its y
 * raised by the pool's own offset. A pool in mode 0 hands out the first slot
 * whose in-use flag is clear; a pool in mode 1 hands them out in turn from a
 * cursor shared by every pool, wrapping once the advanced cursor passes the
 * slot count. Returns the slot index, or -1 for any other mode and for a
 * mode 0 pool with nothing free.
 */

typedef unsigned char u8;
typedef unsigned short u16;

struct VecFx32 {
    int x;
    int y;
    int z;
};

/* Ov022AnimationSlot */
struct AnimationSlot {
    u8 bInUse;                       /* 0x000 */
    u8 pad001[3];
    u16 anim[82];                    /* 0x004 */
    struct VecFx32 vecPos;           /* 0x0a8 */
    u8 pad0b4[0x60];
};

/* Ov022RootHeap */
struct SlotPool {
    u8 nSpare0 : 2;                  /* 0x000 */
    u8 nCount : 6;
    u8 nMode : 3;                    /* 0x001 */
    u8 nSpare1 : 5;
    u8 pad002[2];
    int nYOffset;                    /* 0x004 */
    u8 pad008[4];
    struct AnimationSlot *pSlots;    /* 0x00c */
};

struct PoolOwner {
    u8 pad00[0x20];
    struct SlotPool *pPool;          /* 0x020 */
};

/* Cursor shared by every mode 1 pool. */
extern int data_ov022_020b2ea0;

extern void func_ov022_020892f0(u16 *pAnim, int nArg);

int func_ov022_020891d4(struct PoolOwner *pOwner, struct VecFx32 *pvecPos)
{
    struct VecFx32 vecPos;
    struct AnimationSlot *pSlot;
    int nSlot;
    struct SlotPool *pPool;
    int nCount;
    int nNext;
    int *pCursor;
    int nRet;

    pPool = pOwner->pPool;
    nRet = -1;
    vecPos = *pvecPos;
    vecPos.y = vecPos.y + pPool->nYOffset;
    switch (pPool->nMode) {
    case 0:
        nSlot = 0;
        nCount = pPool->nCount;
        if (nCount > 0) {
            pSlot = pPool->pSlots;
            do {
                if (pSlot->bInUse == 0) {
                    pSlot->bInUse = 1;
                    func_ov022_020892f0(pSlot->anim, 0);
                    pSlot->vecPos = vecPos;
                    nRet = nSlot;
                    break;
                }
                nSlot = nSlot + 1;
                pSlot = pSlot + 1;
            } while (nSlot < nCount);
        }
        break;
    case 1:
        nRet = data_ov022_020b2ea0;
        pSlot = &pPool->pSlots[nRet];
        pSlot->bInUse = 1;
        func_ov022_020892f0(pSlot->anim, 0);
        pCursor = &data_ov022_020b2ea0;
        pSlot->vecPos = vecPos;
        nRet = *pCursor;
        nNext = nRet + 1;
        nCount = pPool->nCount;
        *pCursor = nNext;
        if (nCount < nNext) {
            *pCursor = 0;
        }
        break;
    }
    return nRet;
}
