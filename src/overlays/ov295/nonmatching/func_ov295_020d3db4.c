/* ov295 (byte-identical with ov296) — small per-tick handler (116B). When the actor's
 * low flag bit is set: latch the sub-state byte and emit a positioned event. NEAR-MATCH
 * (120B, +4): the {p[0], p[1]+0x900, p[2]} descriptor build differs by one instruction —
 * the ROM loads all three words via a single `ldm {r2,r3,ip}`, bumps the middle register
 * in place, then stores; mwcc (any source form tried) either splits the load (ldmib+ldr)
 * or block-copies then reloads. An mwcc load-coalescing detail, not a logic difference. */
extern void func_020c5c54(int a, void *desc);
extern void func_0203c634(int a, int b, int c);

struct hw { unsigned short lo : 8, hi : 8; };
struct blk3 { int x, y, z; };

void func_ov295_020d3db4(int param_1, int p2, int p3, int param_4) {
    int *piVar1 = *(int **)(param_1 + 4);
    int iVar3 = *piVar1;
    if (((struct hw *)(iVar3 + 0x60))->lo & 1) {
        struct blk3 desc;
        *(signed char *)(iVar3 + 0x1c7) = *(signed char *)(iVar3 + 0x1c9);
        desc = *(struct blk3 *)piVar1[1];
        desc.y += 0x900;
        func_020c5c54(*piVar1, &desc);
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    }
}
