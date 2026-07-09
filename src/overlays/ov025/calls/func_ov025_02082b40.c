extern void WM_EndKeySharing_0x02023ad0();
extern int data_ov025_020b49c0;

void func_ov025_02082b40(void) {
    int v = data_ov025_020b49c0;
    if (v == -1) {
        return;
    }
    WM_EndKeySharing_0x02023ad0(v);
}
