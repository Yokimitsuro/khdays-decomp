extern int *func_ov008_02051198(void);
extern void func_ov008_02050970(int arg0, int arg1);
extern void func_02033b78(int arg0, int arg1);

void func_ov008_02059934(void)
{
    int mode = 6;

    func_ov008_02051198()[3] = 1;
    func_ov008_02050970(mode, mode - 7);
    func_02033b78(0, 1);
}
