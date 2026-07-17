/*
 * func_ov029_020b2ee0 -- UNFINISHED, and it is the LAST function in ov029 (1/2 -> 2/2).
 * ★ THIS FUNCTION IS **THUMB**. Verify with `--thumb` or every number you get is noise.
 *
 * 96/96 bytes, 47/47 instructions. One register assignment + one schedule slot.
 *
 * ✗ WHAT THE PREVIOUS VERSION OF THIS FILE COST: no diagnosis note, and verified as ARM it
 * reads `140 != 96` -- a 44-byte gap that looks like badly wrong C and invites a rewrite.
 * It is not wrong. state.md's sweep did check all 381 parked files in both modes and
 * correctly found no MATCH, but it recorded only match/no-match, which cannot tell
 * "hopeless" from "one register out". This was the latter, for months.
 *
 * WHAT IT DOES: scan the 4 slots of entry `idx` (entries are 0x10 bytes at
 * data_ov029_020b30b0) from slot 3 down. The first slot whose global gate
 * (data_ov029_020b320c, walked downward in step) is -1 while the entry's own value is not
 * -1 wins: its value becomes the result and is published to data_ov029_020b3200[k]. Then
 * notify (0201e470) and call the per-entry, per-slot handler from data_ov029_020b2f70.
 * Note `k` is -1 when no slot wins, so that lookup indexes one row BEFORE the table --
 * flagged for the port, reproduced as-is.
 *
 * ★ PROGRESS THIS PASS (keep it): `idx` is shifted IN PLACE and reused as the offset.
 * That is what puts `r = -1` before `entry` in the emission order, matching the ROM, and
 * it took the diff 0x3 -> 0x2. A separate `int off` local -- however declared or ordered --
 * always emits `entry` first. So the original really did reuse the parameter.
 *
 * THE DIFF, what is left:
 *      ROM:   ldr r2,[pc] (base) ; lsls r1,r1,#4 (off stays in the PARAM register)
 *             ... adds r7,r2,r1 (entry->r7) ; str r1,[sp] (off SPILLED to the pushed r3 slot)
 *      mine:  lsls r7,r1,#4 (off promoted to callee-saved r7) ; ldr r1,[pc] (base)
 *             ... mov ip,r1 (entry banished to the high register)
 * The loop needs all 8 low THUMB registers (t, e, -1, -1, k, r, temp, entry), so one of
 * off/entry cannot stay low. The ROM spills off and keeps entry low; mwcc keeps off in r7
 * and pays `mov r0, ip` before each indexed load (THUMB's `ldr rd,[rn,rm]` needs low
 * registers). The two cost exactly the same -- 47 instructions either way -- which is
 * presumably why mwcc sees no reason to prefer the ROM's choice.
 *
 * PRE-PARK CHECKLIST:
 *  1. --thumb: YES, and it is the whole point of this note.
 *  2. Arity: 0201e470(0, r) -- the ROM sets r0/r1 only; the handler takes none. arg0 is a
 *     real parameter and unused (r0 is never read).
 *  3. No constant is misplaced: the -1 is in a register and copied to both comparison
 *     operands exactly as the ROM does.
 *  4. Diff read back: 47 vs 47, same opcodes and order.
 *
 * RULED OUT (14 spellings; the last two entries are the ones worth not repeating):
 *   off inlined as (idx<<4) at both uses · off/entry as separate statements · entry
 *   declared before off · the tail through a `void (**tbl)(void)` local · a `char *tb`
 *   base for the tail · `unsigned int off` · `&entry[3]` vs `entry + 3` · comparisons
 *   against `r` instead of the literal -1 (arguably MORE faithful -- the ROM copies r5
 *   into both r2 and r3 -- but identical output) · entry as `char *` with casts at the
 *   load · a copy of idx shifted at the end · a for-loop instead of the do-while (100 B,
 *   4 OVER -- the do-while is required) · `e = (entry = ...) + 3` as one expression
 *
 * NEXT STEP: make mwcc prefer spilling `off` over promoting it to r7. Everything tried
 * changes what off IS; nothing has changed how badly it wants a register. Since both
 * choices cost 47 instructions, the lever is probably not in this function's own
 * expressions at all -- it may need one more value live across the loop.
 */
extern void func_0201e470();
extern char data_ov029_020b30b0[];
extern int data_ov029_020b320c[];
extern int data_ov029_020b3200[];
extern char data_ov029_020b2f70[];

int func_ov029_020b2ee0(int arg0, int idx)
{
    int r = -1;
    int *entry;
    int *t = data_ov029_020b320c;
    int *e;
    int k = 3;

    idx = idx << 4;
    entry = (int *)(data_ov029_020b30b0 + idx);
    e = entry + 3;
    do {
        if (*t == -1 && *e != -1) {
            r = entry[k];
            data_ov029_020b3200[k] = r;
            break;
        }
        t--; e--; k--;
    } while (k >= 0);
    func_0201e470(0, r);
    (*(void (**)())(data_ov029_020b2f70 + idx + k * 4))();
    return r;
}
