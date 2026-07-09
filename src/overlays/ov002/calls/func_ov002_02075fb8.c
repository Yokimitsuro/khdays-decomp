extern void WM_EndKeySharing_0x02023ad0();
extern int data_ov002_0207fa18;

void func_ov002_02075fb8(void) {
    int p = *(int *)((char *)&data_ov002_0207fa18 + 4);
    if (p != 0) {
        WM_EndKeySharing_0x02023ad0(p);
        *(int *)((char *)&data_ov002_0207fa18 + 4) = 0;
    }
}
