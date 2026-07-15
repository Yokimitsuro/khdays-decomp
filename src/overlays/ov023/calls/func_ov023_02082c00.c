/* func_ov023_02082c00 -- end the pending key-sharing session if one is registered,
 * ov023 (handle @data_ov023_0208a000, -1 = none). */
extern void WM_EndKeySharing_0x02023ad0(void *handle);
extern int data_ov023_0208a000;
void func_ov023_02082c00(void) {
    if (data_ov023_0208a000 != -1) {
        WM_EndKeySharing_0x02023ad0((void *)data_ov023_0208a000);
    }
}
