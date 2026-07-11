/* NONMATCHING - register-coloring tie (one extra callee-saved push).
 *
 * Body is byte-shape identical: null-check, a 3-word ldm/stm block copy of *param_1
 * into the global DEST, then an RMW that clears bits 0x24|0x80 (bic #0xa4) of the
 * hardware/control word at data_02047394+0xd4. The ROM stays a LEAF: it loads DEST's
 * address into r3, does ldm r0/stm r3 (reusing r0-r2), then reuses the now-dead r0 for
 * the second pool pointer - four scratch regs, no push. Every mwcc build hoists BOTH
 * pool-address loads up front, spilling the second into lr (a callee-saved), which
 * forces push/pop {r3,lr} (52 vs 48 bytes). Volatile on the RMW, compound-assign and
 * 136 all still hoist; swept 27 builds x 5 opts, none matches. Consistent with retail
 * = 3.0 build >=140. One of a dedup pair (func_02015880/func_020158b0). Blob byte-exact.
 *
 * Publish a 3-word payload from param_1 into the DEST latch, then clear the two enable
 * bits (0x04|0x20 << 2 = 0xa4) in the hardware control word at data_02047394+0xd4. */
typedef struct { unsigned int a, b, c; } Payload3;
extern Payload3 data_02047458;
extern char data_02047394[];
void func_020158b0(unsigned int *param_1) {
    if (param_1 == 0) return;
    data_02047458 = *(Payload3 *)param_1;
    *(unsigned int *)(data_02047394 + 0xd4) = *(unsigned int *)(data_02047394 + 0xd4) & 0xffffff5b;
}
