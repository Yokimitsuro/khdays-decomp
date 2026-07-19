extern int CARD_GetResultCode_0x0202bfb8(void);
extern void func_0202bda4(int mask, int a);
extern void func_ov023_02083508(void);
extern void func_0202bc90(unsigned short id);
extern void func_ov023_0208357c(void);
extern void func_ov023_02083604(void);
extern char *data_ov023_0208a784;

/* Drops a peer that has gone away: unless it is still in state 2 or 3, clears its bit, rebuilds
 * the roster and republishes the lobby. */
void func_ov023_020834c0(int peer) {
    int state;
    if (CARD_GetResultCode_0x0202bfb8() <= peer) {
        return;
    }
    state = *(int *)((&data_ov023_0208a784)[1] + 0x875e4);
    if (state != 3 && state != 2) {
        func_0202bda4(1 << peer, 1 << 0xc);
    }
    func_ov023_02083508();
    func_0202bc90((unsigned short)peer);
    func_ov023_0208357c();
    func_ov023_02083604();
}
