/*
 * func_ov029_020b2ee0 -- Ov029_AcquireOverlaySlot. UNFINISHED (96/96 bytes, no match).
 * It is the LAST function in ov029 (1/2 -> 2/2), so matching it closes the module.
 *
 * * THIS FUNCTION IS **THUMB**. Verify with `--thumb` or every number you get is noise.
 *
 * WHAT IT DOES (resolved 2026-07-19; the older note described it as generic "slots"):
 *   func_0201e470 wraps **FS_LoadOverlay**, and func_0201e4a8, used by the other function
 *   in this overlay, wraps **FS_UnloadOverlay**. So the two ov029 functions are a
 *   load/unload pair over a table of 4 slots:
 *
 *     data_ov029_020b3200[4]   the 4 slots; each holds the id of the overlay currently
 *                              loaded in it, or -1 if free.
 *     data_ov029_020b30b0[]    rows of 4 ints: for each "group", which overlay id belongs
 *                              in each slot (-1 = that group cannot use that slot).
 *     data_ov029_020b2f70[]    rows of 4 function pointers: the init hook for each
 *                              (group, slot) pair.
 *
 *   It walks the slots from 3 down to 0 and takes the first one that is free AND that the
 *   group has an overlay for. Publishes it into the slot, calls FS_LoadOverlay, runs the
 *   hook. Returns the loaded id, or -1 if there was no room.
 *   func_ov029_020b2f40 is the release half: finds the slot holding that id, sets it to -1.
 *
 * ⚠ FOR THE PORT: if no slot is free, k stays -1 and the code carries on regardless. It
 *   calls FS_LoadOverlay(0, -1) and then indexes the hook table with k = -1, i.e. it reads
 *   the word BEFORE the row. That is an out-of-bounds read, reproduced as-is because it is
 *   what the ROM does. Do not silently "fix" it when porting; decide it separately.
 *
 * ⚠ data_ov029_020b3200 AND data_ov029_020b320c ARE THE SAME ARRAY: delinks.txt puts .data
 *   at 0x020b3200..0x020b3220 and 0x320c falls inside it, so it is &array[3]. The original
 *   source wrote one array and took its last element; the two symbols are a delinker
 *   artifact. Both are kept here because verify_idx matches relocs by NAME and the index
 *   expects data_ov029_020b320c at offset 84. (The single-array spelling was tested: same
 *   residue, and it changes the relocs, so it buys nothing.)
 *
 * ---------------------------------------------------------------------------------
 * THE DIFF
 *
 * The loop needs all 8 low THUMB registers, and there are TWO claimants for the single free
 * callee-saved register (r7):
 *   - the byte offset `group << 4`, live across the bl near the end
 *   - the group pointer, dead before that bl
 * ROM:  spills the offset into the pushed r3 slot (`str r1,[sp]` ... `ldr r0,[sp]`) and
 *       keeps the group pointer in a low register (r7).
 * mwcc: gives r7 to the offset and evicts the pointer to `ip`, paying `mov r0, ip` before
 *       the indexed load (THUMB's `ldr rd,[rn,rm]` needs low registers).
 *
 * The offset's live range STARTS FIRST -- it has to, because the pointer is computed FROM
 * it -- so the allocator reaches the offset first and hands it r7.
 *
 * ⚠ CORRECTED 2026-07-19: this note used to say "47/47 instructions", and neither half was
 * true. Measured with capstone over both objects: the ROM has **39** instructions and ours
 * has **38 real ones plus a `mov r8,r8` pad** to align the pool. It is NOT
 * instruction-for-instruction identical: it is one SHORTER, and the 96 bytes only line up
 * because of the nop. That kills the old conclusion ("both cost the same, so mwcc has no
 * reason to prefer the ROM's shape"): mwcc DOES have a reason, its version is shorter.
 * Real counts:
 *      head: ROM 13 / ours 12     loop: ROM 16 / ours 17 (the `mov r0, ip`)
 *      tail: ROM  6 / ours  5     (no need to reload the offset from [sp])
 *
 * ---------------------------------------------------------------------------------
 * AXES ALREADY CLOSED (do not repeat these)
 *
 * COMPILER: full build_sweep. All 12 builds on the 2.0/3.0 line give a byte-identical
 *   residue (54 bytes); the 1.2 and dsi lines do not even hit the right size.
 *
 * FLAGS: took the flags from all nine NDS presets on decomp.me
 *   (/api/preset?platform=nds_arm9) and tried the ten we do not already use: -ipa file,
 *   -ipa function, -fp soft, -str reuse, -str noreuse, -sym on, -RTTI off, -msgstyle gcc,
 *   -nosyspath. All ten give the SAME 54-byte residue. The -ipa pair (interprocedural
 *   analysis) were the only ones with a real chance and they change nothing here.
 *
 * STRUCT TYPING (2026-07-19, suggested on the decomp.me Discord): six formulations tried
 *   (shared byte offset, plain `table[group]` indexing, typed row pointer, group indexed by
 *   k, slot indexed by k). None match. The plain-indexing one matches the ROM's instruction
 *   count (39, no pad) but still parks the pointer in `ip` and changes the relocs. The typed
 *   version was kept anyway because it reads far better, which was the point.
 *
 * SOURCE FORM: ~19 spellings ruled out before that -- a separate `off` local vs reusing the
 *   parameter, the pointer declared first, a `char *` base, walking pointers, `for` instead
 *   of `do/while` (100 B, 4 over), computing `e` first (100 B), one-expression decl-inits,
 *   comparing against `loaded` instead of the literal -1, `unsigned int` on the offset,
 *   `&x[3]` vs `x + 3`.
 *
 * NEXT STEP: none at the function level. It would take an idiom that forces mwcc to spill a
 * value into the pushed argument slot instead of taking the last callee-saved register, or
 * that shortens the group pointer's live range so it wins r7. Asked on the decomp.me
 * Discord. See the register-choice class in deferred-ties.md.
 */
typedef void (*OverlayInitFn)(void);

/* One row per group: which overlay id belongs in each slot (-1 = group can't use it). */
typedef struct {
    int overlayId[4];
} OverlayGroup;

/* One row per group: the init hook for each (group, slot) pair. */
typedef struct {
    OverlayInitFn init[4];
} OverlayInitRow;

extern OverlayGroup   data_ov029_020b30b0[];  /* group table */
extern OverlayInitRow data_ov029_020b2f70[];  /* init hooks, one row per group */
extern int data_ov029_020b3200[4];            /* slots: loaded overlay id, or -1 if free */
extern int data_ov029_020b320c[];             /* == &data_ov029_020b3200[3]; see note above */
extern void func_0201e470(int proc, int overlayId);   /* wraps FS_LoadOverlay */

int func_ov029_020b2ee0(int proc, int group)
{
    int loaded = -1;
    OverlayGroup *g;
    OverlayInitRow *hooks;
    int *slot = data_ov029_020b320c;   /* walks the slots from 3 down to 0 */
    int *cand;                         /* ...alongside the group's id for that slot */
    int k = 3;

    /* group becomes a byte offset and is reused for both tables. That is what the ROM does,
       and it is what pins the emission order (see the diff note above). */
    group = group << 4;
    g = (OverlayGroup *)((char *)data_ov029_020b30b0 + group);
    cand = &g->overlayId[3];
    do {
        if (*slot == -1 && *cand != -1) {
            loaded = g->overlayId[k];
            data_ov029_020b3200[k] = loaded;
            break;
        }
        slot--; cand--; k--;
    } while (k >= 0);

    func_0201e470(0, loaded);
    hooks = (OverlayInitRow *)((char *)data_ov029_020b2f70 + group);
    hooks->init[k]();
    return loaded;
}
