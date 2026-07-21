extern void WM_EndKeySharing_0x02023ad0(int handle);
extern char data_ov027_02083ee0[];
/* Tear down the key-sharing session if one is open (handle at +4 is not -1). */
void func_ov027_02082ad8(void) {
    int handle = *(int *)(data_ov027_02083ee0 + 4);
    if (handle != -1) {
        WM_EndKeySharing_0x02023ad0(handle);
    }
}
