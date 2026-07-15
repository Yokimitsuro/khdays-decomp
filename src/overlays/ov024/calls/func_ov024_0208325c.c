/* func_ov024_0208325c -- end the pending key-sharing session if one is registered,
 * ov023 (handle @data_ov024_02093900, -1 = none). */
extern void WM_EndKeySharing_0x02023ad0(void *handle);
extern int data_ov024_02093900;
void func_ov024_0208325c(void) {
    if (data_ov024_02093900 != -1) {
        WM_EndKeySharing_0x02023ad0((void *)data_ov024_02093900);
    }
}
