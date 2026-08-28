typedef unsigned char u8;

extern char *data_ov002_0207fa14;   /* g_pOv002ObjectContext */

extern void func_ov002_02074054(int nArg);  /* Ov002_SetCurrentSlotFlag1 */
extern int func_02030670(void);                 /* Session_IsActive */
extern int func_02030788(void);                 /* Session_GetLocalPlayerIndex */
extern int func_ov002_0206fb84(int nKind, void *pCmd);  /* send, or 0xffff */
extern int func_01fff974(void);                 /* the peer mask */

/* Drives the two-sided handshake that settles which peers are in, and reports
 * whether it is finished.
 *
 * With the session no longer active, or once bit 7 of the flag byte at +0x54
 * is up, there is nothing left to do and the answer is true.  Otherwise the
 * two sides take different halves, chosen by the local player index.
 *
 * Ghidra models the block as Ov002ObjectContext: nSeqOut at +0x52, nSeqAck at
 * +0x53 and bHandshake at +0x54.
 *
 * The compound assignments matter: written out as x = (u8)(x | k), mwcc reuses
 * a byte it loaded earlier and the function comes out four bytes short.
 *
 * The host, whose index is zero, starts the handshake: while its own byte is
 * still clear and the two counters agree, it sends kind 0xe carrying the
 * counter and, if that got through, marks the request sent and armed.  Once
 * the byte is no longer clear it instead waits for the request bit and for the
 * low four bits to match the peer mask, and calls the handshake done.
 *
 * The other side answers: while the answer bit is up and the counters agree,
 * it sends kind 0xf carrying its own index and, if that got through, drops the
 * answer bit and calls the handshake done.
 *
 * A send that comes back 0xffff could not reach the network, and the pass is
 * simply dropped so the next frame tries again.
 */
#pragma opt_common_subs off
int func_ov002_020735bc(void)
{
    char *pCtx;
    int bDone;
    u8 aCmd[4];

    pCtx = data_ov002_0207fa14;
    bDone = 0;
    func_ov002_02074054(bDone);

    if (func_02030670() != 0) {
        if ((*(u8 *)(pCtx + 0x54) & 0x80) != 0) {
            bDone = 1;
        } else if (func_02030788() == 0) {
        if (*(u8 *)(pCtx + 0x54) == 0) {
            if (*(u8 *)(pCtx + 0x52) == *(u8 *)(pCtx + 0x53)) {
                aCmd[3] = *(u8 *)(pCtx + 0x52);
                if (func_ov002_0206fb84(0xe, &aCmd[2]) != 0xffff) {
                    *(u8 *)(pCtx + 0x54) = (u8)(*(u8 *)(pCtx + 0x54) | 0x10);
                    *(u8 *)(pCtx + 0x54) = (u8)(*(u8 *)(pCtx + 0x54) | 1);
                }
            }
        } else if ((*(u8 *)(pCtx + 0x54) & 0x10) != 0) {
            if ((*(u8 *)(pCtx + 0x54) & 0xf) == func_01fff974()) {
                *(u8 *)(pCtx + 0x54) |= 0x80;
            }
        }
    } else if ((*(u8 *)(pCtx + 0x54) & 0x20) != 0) {
        if (*(u8 *)(pCtx + 0x52) == *(u8 *)(pCtx + 0x53)) {
            aCmd[1] = (u8)func_02030788();
            if (func_ov002_0206fb84(0xf, aCmd) != 0xffff) {
                *(u8 *)(pCtx + 0x54) = (u8)(*(u8 *)(pCtx + 0x54) & ~0x20);
                *(u8 *)(pCtx + 0x54) = (u8)(*(u8 *)(pCtx + 0x54) | 0x80);
            }
        }
        }
    } else {
        bDone = 1;
    }
    return bDone;
}
#pragma opt_common_subs on
