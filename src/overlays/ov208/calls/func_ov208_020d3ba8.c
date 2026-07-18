/*
 * func_ov208_020d3ba8 -- x3 (ov208/209/268). Latch a 1-bit state flag, then tail-call the shared tick.
 * When *(u8)(node+2) == 0, set *(s8)(node+0x24) = (char)((*(*(self+0x384)+0x5c) << 30) >> 31), i.e.
 * bit 1 of that word sign-extended. Then tail-call 020c7a90(self, node).
 */
extern void func_ov107_020c7a90(int self, int node, int arg3);

void func_ov208_020d3ba8(int self, int node, int arg3) {
    if (*(unsigned char *)(node + 2) == 0) {
        *(signed char *)(node + 0x24) =
            (signed char)((*(int *)(*(int *)(self + 0x384) + 0x5c) << 30) >> 31);
    }
    func_ov107_020c7a90(self, node, arg3);
}
