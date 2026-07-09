extern char *func_ov008_02050cd4(void);
extern void WM_EndKeySharing_0x0205c574(void *context, int arg0, int arg1, int arg2);

void func_ov008_0205b7d0(int arg0, int arg1, int arg2)
{
    WM_EndKeySharing_0x0205c574(func_ov008_02050cd4() + 4, arg0, arg1, arg2);
}
