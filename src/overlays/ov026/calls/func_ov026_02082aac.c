extern void WM_EndKeySharing_0x02023ad0(int handle);
extern char *data_ov026_02091360;
/* Close the session's key-sharing handle (ctx+8) when a session exists. */
void func_ov026_02082aac(void) {
    int ctx = (int)data_ov026_02091360;
    if (ctx == 0) {
        return;
    }
    WM_EndKeySharing_0x02023ad0(*(int *)(ctx + 8));
}
