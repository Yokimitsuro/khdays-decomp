/*
 * Drains the pending peer notices, one per peer, once a frame.
 *
 * Each peer that has a notice waiting gets a two-byte command built on the
 * stack, carrying its slot in the low three bits and its ready flag in the
 * next one, and handed to the sender as kind 0x16. A notice is only cleared
 * once the sender has taken it; if the sender refuses, the pass stops there
 * and leaves the rest for the next frame.
 *
 * One thing here is load-bearing rather than style. The ready flag is masked
 * to its low bit before it is assigned to the one-bit field. The field's own
 * insert already discards the upper bits, so without the mask the compiler
 * drops the `and` and the function comes out one instruction short.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned int u32;

typedef struct Ov002PeerCmd {
    u8 nPad;
    u8 nSlot : 3;
    u8 bReady : 1;
} Ov002PeerCmd;

typedef struct Ov002RootContext {
    char pad0000[0x8db7];
    u8 aPending[4];
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;

extern int func_ov002_0206fb84(int nKind, void *pCmd);

void func_ov002_0206dec4(void)
{
    Ov002RootContext *pCtx;
    Ov002PeerCmd cmd;
    int i;

    pCtx = data_ov002_0207fa00;
    for (i = 0; i < 4; i++) {
        if (pCtx->aPending[i] != 0) {
            cmd.nSlot = (u8)i;
            cmd.bReady = pCtx->aPending[i] & 1;
            if (func_ov002_0206fb84(0x16, &cmd) == 0xffff) {
                return;
            }
            pCtx->aPending[i] = 0;
        }
    }
}
