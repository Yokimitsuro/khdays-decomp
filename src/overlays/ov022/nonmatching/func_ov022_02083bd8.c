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
 */
extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_0201e4a8(int arg0, int arg1);
extern int data_ov022_020b2e60;
extern int data_0204be04;

int func_ov022_02083bd8(void) {
    if (*(int *)((char *)&data_ov022_020b2e60 + 8) != 0) {
        WM_EndKeySharing_0x02023ad0(*(int *)((char *)&data_ov022_020b2e60 + 8));
        *(int *)((char *)&data_ov022_020b2e60 + 8) = 0;
        *(unsigned char *)&data_0204be04 = 0;
        func_0201e4a8(0, 0x6a);
    }
    return 0;
}
