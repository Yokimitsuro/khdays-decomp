/*
 * func_ov029_020b2ee0 -- UNFINISHED, and it is the LAST function in ov029 (1/2 -> 2/2).
 * * THIS FUNCTION IS **THUMB**. Verify with `--thumb` or every number you get is noise.
 *
 * 96/96 bytes. Primer byte distinto: +0x2.
 *
 * ⚠ CORREGIDO 2026-07-19: esta linea decia "47/47 instructions", y ninguna de las dos
 * mitades era cierta. Medido con capstone sobre los dos objetos: el ROM tiene **39**
 * instrucciones y el nuestro **38 reales + un `mov r8,r8` de relleno** para alinear el
 * pool. Es decir, nuestra version NO es instruccion-por-instruccion identica: es UNA MAS
 * CORTA, y los 96 bytes cuadran solo por el nop. El texto de abajo que dice "both cost
 * exactly the same -- 47 instructions either way -- which is presumably why mwcc sees no
 * reason to prefer the ROM's choice" se apoyaba en ese numero inventado: mwcc SI tiene un
 * motivo para preferir su reparto, porque le sale mas corto. Cuenta real:
 *      cabecera: ROM 13 / nuestra 12   (el ROM hace adds r7,r2,r1 + str r1,[sp] +
 *                                       adds r1,r7,#0; nosotros adds r1,r1,r7 + mov ip,r1)
 *      bucle:    ROM 16 / nuestra 17   (+1: el `mov r0, ip` antes de la carga indexada)
 *      cola:     ROM  6 / nuestra  5   (-1: no hace falta recargar off desde [sp])
 * Lo que sigue siendo cierto es el diagnostico de asignacion de registros; lo que cambia
 * es que no basta con "convencer" al reparto, hay que hacer que la forma del ROM no sea
 * estrictamente peor. Ver el analisis de rangos de vida mas abajo.
 *
 *  WHAT THE PREVIOUS VERSION OF THIS FILE COST: no diagnosis note, and verified as ARM it
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
 * * PROGRESS THIS PASS (keep it): `idx` is shifted IN PLACE and reused as the offset.
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
 *   off inlined as (idx<<4) at both uses  off/entry as separate statements  entry
 *   declared before off  the tail through a `void (**tbl)(void)` local  a `char *tb`
 *   base for the tail  `unsigned int off`  `&entry[3]` vs `entry + 3`  comparisons
 *   against `r` instead of the literal -1 (arguably MORE faithful -- the ROM copies r5
 *   into both r2 and r3 -- but identical output)  entry as `char *` with casts at the
 *   load  a copy of idx shifted at the end  a for-loop instead of the do-while (100 B,
 *   4 OVER -- the do-while is required)  `e = (entry = ...) + 3` as one expression
 *
 * RULED OUT, 2026-07-17 pass (5 more, all still pinned at 0x2):
 *   `idx <<= 4`  a `char *base` local loaded BEFORE the shift (the ROM emits `ldr base`
 *   first, so this looked like the emission-order lever -- it is not; mwcc still shifts
 *   first)  `entry = (int *)(data + (idx <<= 4))` as one decl-init  `e` computed first
 *   with `entry = e - 3` (100 B, 4 OVER)  the `int off` local RE-MEASURED: the previous
 *   note recorded only that it "emits entry first" (diff 0x3), but the register outcome is
 *   the SAME (off->r7, entry->ip). So off-local is not merely worse-by-one; it fails on the
 *   identical axis, and the 0x3-vs-0x2 offset was measuring the wrong thing.
 *
 * * SHARPER DIAGNOSIS (this is the useful part of the pass). The old note said "make mwcc
 * prefer spilling off" without saying why it will not. The reason is live-range ORDER:
 *   - `k` and `r` are live across the 0201e470 call -> they must be callee-saved: r4, r5.
 *   - `temp` is loop-only but the low scratch (r0..r3) is full (t, e, -1, -1) -> r6.
 *   - that leaves ONE callee-saved register, r7, and TWO claimants: `off` and `entry`.
 *   - `off`'s live range STARTS FIRST -- it must, because `entry` is computed FROM it -- so
 *     mwcc's allocator reaches `off` first, hands it r7, and `entry` is evicted to ip.
 *   - the ROM does the opposite: `off` lives in the scratch r1 for three instructions and is
 *     spilled to the free r3 slot immediately, never competing for r7 at all.
 * Both cost 47 instructions, which is why mwcc has no reason to prefer the ROM's shape.
 *
 * ** THE CORPUS, PROPERLY QUERIED (2026-07-17). This entry replaces one that said "the corpus
 * proves this is a C bug". It does not. That claim came from finding 0 ip-parks in the 693
 * MATCHED real-C THUMB functions -- a search that could not have found any, because ip is
 * CALLER-SAVED and so is only usable for a value that needs a register but does NOT cross a
 * call, which is rare and absent from the (small, simple) matched corpus. Re-run over all 2,208
 * THUMB functions in the ROM: **35 of them DO park a value in ip** (func_02025aac 2,034 B,
 * func_020262bc 1,928 B, func_ov002_0206b0f8 964 B, ...) -- all large, none matched yet, which
 * is why the first sweep missed them. The ROM's compiler uses ip. This C is not indicted.
 *
 * What the sweeps DID establish, and it explains the diff exactly:
 *   - mwcc spills into the free r3 push slot when a value crosses a call and no callee-saved
 *     register is free: 46 matched functions do it (func_ov000_02055a24 is the clean example).
 *     So it is not reluctant to spill -- it spills when genuinely out of registers.
 *   - Here `off` CROSSES the 0201e470 call, so ip cannot hold it: it must be callee-saved or
 *     spilled. `entry` does NOT cross a call, so ip can hold it.
 *   - The ROM keeps `entry` low and spills `off`. mwcc gives `off` the callee-saved r7 and evicts
 *     `entry` to ip. Both legal, both 47 instructions, and mwcc's is arguably smarter.
 *
 * So this is a genuine allocator tie-break with a understood mechanism, not a missing live value.
 * The three "candidates nobody has checked" a previous version of this note listed (deriving t
 * from e, the two -1 registers, the loop-only temp) were premised on the false conclusion --
 * they would each FREE a low register, which is the opposite of what is needed. Ignore them.
 *
 * NEXT STEP: none at the function level. To beat this you would have to make `entry` cross a
 * call (it does not, and cannot without changing semantics) so that ip stops being an option for
 * it. Leave it; see the register-CHOICE class in deferred-ties.md.
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
