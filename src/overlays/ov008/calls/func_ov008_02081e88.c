extern char *data_ov008_02090fa8;
extern void WM_EndKeySharing_0x02023ad0(int arg0);
extern void func_0200108c(void);
extern void func_02003948(int arg0);

void func_ov008_02081e88(void)
{
    WM_EndKeySharing_0x02023ad0(*(int *)data_ov008_02090fa8);

    if (*(int *)(data_ov008_02090fa8 + 4) == 2) {
        func_0200108c();
        func_02003948(-2);
    }
}
