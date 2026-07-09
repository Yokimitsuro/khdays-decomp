extern int func_ov008_02050cd4(void);
extern void WM_EndKeySharing_0x0205665c(int, int);
void func_ov008_0205b6c8(int value)
{
    WM_EndKeySharing_0x0205665c(func_ov008_02050cd4() + 0x13fc, value);
}
