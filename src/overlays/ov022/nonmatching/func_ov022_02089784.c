/*
 * [nonmatching: register-representation tie — 84B vs 88B, structurally byte-identical]
 *
 * Writes a 3-word payload from arg0 into a slot indexed by (idx & 7), where
 * idx = the u16 at arg0+2, base = *data_ov022_020b2ea4 + 0x14.
 *
 * The original materializes (idx & 7) as `lsl ip,idx,#0x1d; lsr lr,ip,#0x1d`
 * (2 instrs) and REUSES the intermediate `ip` at the end via
 * `add r0, base, ip, lsr #29` to form `base + (idx & 7)`. mwcc 3.0/139 instead
 * lowers `idx & 7` to a single `and #7` and forms the final address with a
 * plain `add r0, base, m` — a shorter (84B) but equivalent codegen. No source
 * form (`idx & 7`, `(idx<<0x1d)>>0x1d`, inline vs. hoisted) makes mwcc keep the
 * longer shift-reuse representation, so this is left uncarved (byte-exact in the
 * blob) with the clean equivalent C recorded here.
 */
typedef struct { int a; int b; int c; } Vec3w;

extern int data_ov022_020b2ea4;

void func_ov022_02089784(unsigned int *arg0) {
    unsigned int idx = *(unsigned short *)((int)arg0 + 2);
    int base = *(int *)&data_ov022_020b2ea4 + 0x14;
    int e = (idx & 7) * 0xc + base;
    *(unsigned short *)((idx & 7) * 6 + base + 0x84) = (unsigned short)((idx << 0x11) >> 0x14);
    *(Vec3w *)(e + 0x14) = *(Vec3w *)arg0;
    *(unsigned char *)(base + (idx & 7) + 0x10) = 1;
}
