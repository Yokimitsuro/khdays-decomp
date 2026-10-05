/* Claim a free effect slot and launch it at the given position, facing away from `dir`.
 *
 * Scans the seven 0x10c-byte slots for one whose first word is clear, marks it taken, and
 * primes its three sub-channels with a variant index that cycles 0, 1, 2 off the block's
 * running counter.  The position is copied in and the facing is the REVERSED direction's
 * atan2, with the dirty bit set; the counter is then bumped so the next call gets the next
 * variant.  Does nothing when all seven slots are busy.
 *
 * THREE SPELLINGS, all of which read as scheduling noise if you skip them:
 *  - the search TESTS through a walking pointer but computes the winner from the INDEX
 *    (`mla`).  Both idioms in one loop: `p += 0x10c` for the test, `blk + 0x14 + i * 0x10c`
 *    for the result.  Using one form for both costs bytes either way.
 *  - the variant is `counter % 3`, spelled exactly that way.  Writing it out as
 *    `x - x / 3 * 3` -- which is what the ROM's magic-multiply sequence looks like -- lets
 *    mwcc strength-reduce the multiply-back to `q + q*2` and comes out 4 bytes short.  The
 *    ROM keeps 3 in a register and uses smull, which is what the plain `%` operator emits.
 *    A variable holding 3 does not help; mwcc folds it.
 *  - `i` must be assigned BEFORE the walking pointer, so the loop reads
 *    `i = 0; p = blk; for (; i < 7; i++)`.  Otherwise the two initialising movs come out
 *    swapped -- and that was the last two bytes.
 */

#include "nitro/fx_types.h"

extern void BindAnimTrack(char *p, int i, char *tbl, short m);
extern void Anim_SetFrameWrapped(char *p, int i, int z);
extern int FX_Atan2Idx(int x, int z);
extern char *data_ov098_020bbda0;

void Ov098_ClaimSlotAndLaunch(VecFx32 *pos, VecFx32 *dir) {
    char *blk = data_ov098_020bbda0 + 0x2c + 0x2c00;
    char *slot = 0;
    char *p;
    int i;
    int k;

    i = 0;
    p = blk;
    for (; i < 7; i++) {
        if (*(int *)(p + 0x14) == 0) {
            slot = blk + 0x14 + i * 0x10c;
            break;
        }
        p = p + 0x10c;
    }
    if (slot == 0) {
        return;
    }

    k = *(int *)(blk + 0xc) % 3;

    *(int *)slot = 1;
    BindAnimTrack(slot + 4, 0, slot + 0xe4, (short)k);
    BindAnimTrack(slot + 4, 2, slot + 0xe4, (short)k);
    BindAnimTrack(slot + 4, 1, slot + 0xe4, (short)k);
    Anim_SetFrameWrapped(slot + 4, 0, 0);
    Anim_SetFrameWrapped(slot + 4, 2, 0);
    Anim_SetFrameWrapped(slot + 4, 1, 0);

    *(VecFx32 *)(slot + 0xa8) = *pos;
    *(short *)(slot + 0x80) = (short)FX_Atan2Idx(-dir->x, -dir->z);
    *(unsigned short *)(slot + 4) |= 0x20;
    *(int *)(blk + 0xc) = *(int *)(blk + 0xc) + 1;
}
