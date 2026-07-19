/*
 * [nonmatching: pool-load-of-encodable-immediate — 44B vs 48B]
 *
 * Frees the slot pointer at data_ov022_020b2e60+8 (if set) via WM_EndKeySharing,
 * clears it and data_0204be04, then calls func_0201e4a8(0, 0x6a).
 *
 * The original loads the constant 0x6a from its literal pool (`ldr r1,[pc,#..]`
 * + a pool word) rather than materializing it (`movs r1,#0x6a`). 0x6a is an
 * encodable THUMB immediate, so mwcc 3.0/139 always emits the `movs`, dropping
 * the pool word (4B short). No source form forces the pool load — the classic
 * linker-absolute / pool-of-encodable-immediate tie. Left uncarved (byte-exact).
 *
 * RE-TESTED 2026-07-20 against the pointer-cast crack (codegen-cracks.md): the C
 * did carry the symptom — `(char *)&data + 8` three times — and it has been
 * rewritten to the array form below, which is cleaner and what the original
 * almost certainly said. It does NOT change the residue: still 44 vs 48.
 * ★ Confirmed the diagnosis instead of overturning it: the pool word at +0x2c
 * has NO RELOC, so 0x6a really is a literal and not a symbol whose value happens
 * to be 0x6a. That was the one cheap way this park could have been wrong.
 * Lesson for the re-test sweep: the cast symptom is a SCREEN, not a verdict —
 * carrying it does not mean it is what blocks the function.
 */
extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_0201e4a8(int arg0, int arg1);
extern int data_ov022_020b2e60[];
extern unsigned char data_0204be04;

int func_ov022_02083bd8(void) {
    if (data_ov022_020b2e60[2] != 0) {
        WM_EndKeySharing_0x02023ad0(data_ov022_020b2e60[2]);
        data_ov022_020b2e60[2] = 0;
        data_0204be04 = 0;
        func_0201e4a8(0, 0x6a);
    }
    return 0;
}
