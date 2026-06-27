extern int *func_02023c00(void);
extern void WM_EndKeySharing_0x02023ad0(int arg);
extern int data_0204c228;

void func_02030550(void) {
    int *p = func_02023c00();
    WM_EndKeySharing_0x02023ad0(p[9]);
    WM_EndKeySharing_0x02023ad0(p[10]);
    data_0204c228 = 0;
}
