extern void WM_EndKeySharing_0x02023ad0(int *ctx);
extern int func_02020aa8(int idx, int value);
extern int *data_ov002_0207fa20;
/* Reset the subsystem: run teardown on the global context and clear global array entry 4; return 1. */
int func_ov002_020763f0(void) {
    WM_EndKeySharing_0x02023ad0(data_ov002_0207fa20);
    func_02020aa8(4, 0);
    return 1;
}
