/*
 * Ov029_AcquireOverlaySlot -- overlay slot allocator.  THUMB.
 *
 * There are 4 slots; each holds the id of the overlay currently loaded in it, or
 * -1 if free.  Each "group" declares which overlay id belongs in which slot, plus
 * an init hook per (group, slot) pair.  func_0201e470 wraps FS_LoadOverlay; the
 * sibling func_ov029_020b2f40 wraps FS_UnloadOverlay and is the release half.
 *
 * Walks the slots from 3 down to 0 and takes the first one that is free AND that
 * the group has an overlay for.  Publishes it, loads it, runs the hook.  Returns
 * the loaded id, or -1 if there was no room.
 *
 * ⚠ FOR THE PORT: if no slot is free, k stays -1 and the code carries on anyway.
 *   It calls FS_LoadOverlay(0, -1) and then indexes the hook table with -1, i.e.
 *   reads the word BEFORE the row.  Out of bounds, and reproduced as-is because
 *   the ROM does it.  Do not silently "fix" this when porting; decide it
 *   separately.
 *
 * ⚠ data_ov029_020b3200 and data_ov029_020b320c are the SAME array.  .data runs
 *   0x020b3200..0x020b3220 and 0x320c falls inside it, so 020b320c is &slots[3].
 *   The original wrote one array; the two symbols are a delinker artifact.  Kept
 *   as two here because verify_idx matches relocs by name.
 *
 * HOW IT MATCHED (the previous write-up claimed struct typing had been exhausted
 * and it had not -- see codegen-cracks.md, "array lookups"):
 *   1. `table[group]` beats `(T *)((char *)table + (group << 4))`.  If you have to
 *      cast pointers back and forth, that is a tell you are transcribing the
 *      machine code rather than the source: a 16-byte stride means a 16-byte
 *      element, so index it.
 *   2. DUPLICATE the lookup instead of caching it in a local.  Writing
 *      `data_ov029_020b30b0[group]` twice is what a game programmer would write;
 *      mwcc re-derives it and the codegen changes.  The earlier attempt did use
 *      plain indexing but kept a cached `g` pointer, which is why it still failed.
 *   3. `base + group + k*4`, two variables scaled by different constants, is a
 *      NESTED ARRAY: `data_ov029_020b2f70[group].initFns[k]()`.
 */
typedef void (*OverlayInitFn)(void);

/* One row per group: which overlay id belongs in each slot (-1 = group can't use it). */
typedef struct {
    int overlayId[4];
} OverlayGroup;

/* One row per group: the init hook for each (group, slot) pair. */
typedef struct {
    OverlayInitFn initFns[4];
} OverlayInitRow;

extern OverlayGroup   data_ov029_020b30b0[];  /* group table */
extern OverlayInitRow data_ov029_020b2f70[];  /* init hooks, one row per group */
extern int data_ov029_020b3200[4];            /* slots: loaded overlay id, or -1 if free */
extern int data_ov029_020b320c[];             /* == &data_ov029_020b3200[3]; see note above */
extern void func_0201e470(int proc, int overlayId);   /* wraps FS_LoadOverlay */

int func_ov029_020b2ee0(int proc, int group)
{
    int loaded = -1;
    int *slot = data_ov029_020b320c;  /* walks the slots from 3 down to 0 */
    int *cand;                        /* ...and alongside it, the group's id for that slot */
    int k = 3;

    cand = &data_ov029_020b30b0[group].overlayId[3];
    do {
        if (*slot == -1 && *cand != -1) {
            loaded = data_ov029_020b30b0[group].overlayId[k];
            data_ov029_020b3200[k] = loaded;
            break;
        }
        slot--; cand--; k--;
    } while (k >= 0);

    func_0201e470(0, loaded);
    data_ov029_020b2f70[group].initFns[k]();
    return loaded;
}
