/* Refresh the live triple and the live value on all four roster slots.
 *
 * The slot array hangs off the session block at root context + 0x8bcc, whose entries pointer
 * sits at +4, so the array itself is reached through +0x8bd0. Slots are 0x44 apart and there
 * are always four. Each slot carries a default triple at +0 and a default value at +0xc,
 * written by func_ov002_02069b14, alongside the live pair at +0x34 and +0x40 that this
 * function drives.
 *
 * A null pSrcVec means "use each slot's own default triple" and nValue == -1 means "use each
 * slot's own default value", so the (0, -1) call in the ov022 teardown path at
 * func_ov022_02083774 restores every slot at once.
 *
 * Codegen note. The destination pointer is assigned redundantly in BOTH arms of the source
 * selection. Assigned once after the merge instead, mwcc forward-substitutes it away and hands
 * its register to the compiler's own struct-copy cursor; assigned once before the branch, it
 * survives but its two setup instructions are hoisted above the compare. Duplicated across the
 * arms mwcc sinks it back into the merge, which costs nothing and is where the ROM has it.
 * Declaring pDst before pSrc, and assigning pSrc before pDst inside each arm, fixes the last
 * register pair; pEntry must be declared at function scope.
 *
 * Ghidra carries this as Ov002_SetRosterSlotTargets over Ov002RosterSlot and Vec3.
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    Vec3 vecBase;               /* +0x00 default triple */
    int nBaseValue;             /* +0x0c default value */
    char aDetail[0x24];         /* +0x10 detail payload */
    Vec3 vecTarget;             /* +0x34 live triple */
    int nTargetValue;           /* +0x40 live value */
} Ov002RosterSlot;

extern char *data_ov002_0207fa00;

void func_ov002_0206ba78(Vec3 *pSrcVec, int nValue) {
    char *pSession = data_ov002_0207fa00 + 0x8bcc;
    Ov002RosterSlot *pEntry;
    int nByteOffset = 0;
    int nIndex = 0;

    do {
        Vec3 *pDst;
        Vec3 *pSrc;

        pEntry = (Ov002RosterSlot *)(*(char **)(pSession + 4) + nByteOffset);
        if (pSrcVec == 0) {
            pSrc = &pEntry->vecBase;
            pDst = &pEntry->vecTarget;
        } else {
            pSrc = pSrcVec;
            pDst = &pEntry->vecTarget;
        }
        *pDst = *pSrc;
        if (nValue == -1) {
            pEntry->nTargetValue = pEntry->nBaseValue;
        } else {
            pEntry->nTargetValue = nValue;
        }
        nIndex++;
        nByteOffset += 0x44;
    } while (nIndex < 4);
}
