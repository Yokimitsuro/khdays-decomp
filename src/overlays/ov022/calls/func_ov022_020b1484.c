extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern int data_ov022_020b2eb8;

void func_ov022_020b1484(void) {
    if (((int *)&data_ov022_020b2eb8)[0] != 0 && ((int *)&data_ov022_020b2eb8)[1] != 0) {
        WM_EndKeySharing_0x02023ad0(((int *)&data_ov022_020b2eb8)[1]);
        ((int *)&data_ov022_020b2eb8)[1] = 0;
    }
}
