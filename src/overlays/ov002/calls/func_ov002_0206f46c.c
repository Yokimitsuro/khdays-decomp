extern void WM_EndKeySharing_0x02023ad0();
extern int data_ov002_0207f024;

void func_ov002_0206f46c(void) {
    int p = *(int *)&data_ov002_0207f024;
    if (p == -1) {
        return;
    }
    WM_EndKeySharing_0x02023ad0(p);
    data_ov002_0207f024 = -1;
}
