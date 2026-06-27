extern void WM_EndKeySharing_0x02023ad0(int arg);

extern int data_02042978;

void func_02030610(void) {
    if (data_02042978 == -1) return;
    WM_EndKeySharing_0x02023ad0(data_02042978);
    data_02042978 = -1;
}
