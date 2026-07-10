extern void func_02030d10(int arg0);
extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern int data_ov022_020b2eac;

void func_ov022_02092354(int *arg0) {
    int c = *(int *)&data_ov022_020b2eac - 1;
    int i;
    *(int *)&data_ov022_020b2eac = c;
    if (c == 0) func_02030d10(10);
    i = 0;
    do {
        if (*arg0 != 0) WM_EndKeySharing_0x02023ad0(*arg0);
        i = i + 1;
        arg0 = arg0 + 1;
    } while (i < 6);
}
