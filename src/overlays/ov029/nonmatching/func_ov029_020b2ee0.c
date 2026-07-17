/*
 * func_ov029_020b2ee0 -- UNFINISHED, and it is the LAST function in ov029 (1/2 -> 2/2).
 * ★ THIS FUNCTION IS **THUMB**. Verify it with `--thumb` or every number you get is noise.
 *
 * 96/96 bytes, 47/47 instructions in THUMB. A register permutation, nothing more.
 *
 * ✗ WHAT THE PREVIOUS VERSION OF THIS FILE COST: it carried no diagnosis note at all, and
 * verified as ARM it reads `140 != 96` -- a 44-byte gap that looks like badly wrong C and
 * invites a rewrite. It is not wrong. The C below is the ORIGINAL parked C, unchanged, and
 * in the right mode it is 47 instructions out of 47. state.md's sweep did verify all parked
 * files in both modes and correctly found no MATCH -- but "no match" threw away how CLOSE
 * each one got, and this one was one register away the whole time.
 *
 * WHAT IT DOES: scan the 4 slots of entry `idx` (each entry is 0x10 bytes at
 * data_ov029_020b30b0) from slot 3 down. The first slot whose global gate
 * (data_ov029_020b320c, walked DOWNWARD in step with the slot) is -1 while the entry's own
 * value is not -1 wins: its value becomes the result and is published to
 * data_ov029_020b3200[k]. Then notify (0201e470) and call the per-entry, per-slot handler
 * out of the table at data_ov029_020b2f70. Note `k` is -1 if no slot won, so the handler
 * lookup indexes one BEFORE the table row -- deliberate or not, it is what the ROM does.
 *
 * THE DIFF (all of it, from 0x3):
 *      ROM:   base=r2  off=r1 (the incoming param register, then SPILLED to [sp])  r=r5  entry=r7
 *      mine:  base=r0  off=r7 (promoted to callee-saved)                           r=r6  entry=ip
 * The ROM keeps `off` in the scratch it arrives in, spills it to the pushed r3 slot, and
 * reloads it for the tail lookup -- because the loop body needs all 8 low registers
 * (t, e, -1, -1, k, r, temp, entry). mwcc instead promotes `off` to r7 and banishes `entry`
 * to the high register ip, avoiding the spill. Both are legal; the instruction COUNT is
 * identical either way.
 *
 * PRE-PARK CHECKLIST:
 *  1. --thumb: YES -- and that is the entire point of this note. ARM gives a meaningless
 *     140 != 96.
 *  2. Arity: 0201e470(0, r) -- the ROM sets r0/r1 only. The handler is called with none.
 *     arg0 is a real parameter and unused (r0 is never read).
 *  3. No constant is in the wrong register: the -1 is present, in a register, and copied to
 *     both comparison operands exactly as the ROM does.
 *  4. Diff read back: 47 vs 47, same opcodes, same order.
 *
 * RULED OUT (7 spellings, all still 96/96 with the diff pinned at 0x3):
 *   off inlined as (idx << 4) at both uses · off/entry as separate statements ·
 *   entry declared before off · the tail lookup through a `void (**tbl)(void)` local ·
 *   `unsigned int off` · `&entry[3]` instead of `entry + 3` ·
 *   the comparisons written against `r` instead of the literal -1 (this one is arguably
 *   MORE faithful -- the ROM copies r5 into both r2 and r3 -- but it changes nothing)
 *
 * NEXT STEP: force mwcc to spill `off` rather than promote it to r7. Everything tried so
 * far changes what off IS, not how badly it wants a register. THUMB has only 8 low
 * registers and the loop needs all of them, so the lever is probably something that makes
 * the loop body need one more -- not something about off itself.
 */
extern void func_0201e470();
extern char data_ov029_020b30b0[];
extern int data_ov029_020b320c[];
extern int data_ov029_020b3200[];
extern char data_ov029_020b2f70[];

int func_ov029_020b2ee0(int arg0, int idx)
{
    int r = -1;
    int off = idx << 4;
    int *entry = (int *)(data_ov029_020b30b0 + off);
    int *t = data_ov029_020b320c;
    int *e = entry + 3;
    int k = 3;
    do {
        if (*t == -1 && *e != -1) {
            r = entry[k];
            data_ov029_020b3200[k] = r;
            break;
        }
        t--; e--; k--;
    } while (k >= 0);
    func_0201e470(0, r);
    (*(void (**)())(data_ov029_020b2f70 + off + k * 4))();
    return r;
}
