/* func_ov004_0204fc98 -- end the current key-sharing session, ov004 (tail-call to
 * WM_EndKeySharing over the doubly-indirected context @data_ov004_02051380). */
extern void *WM_EndKeySharing_0x02023ad0(void *ctx);
extern void *data_ov004_02051380;
void *func_ov004_0204fc98(void) {
    return WM_EndKeySharing_0x02023ad0(*(void **)data_ov004_02051380);
}
