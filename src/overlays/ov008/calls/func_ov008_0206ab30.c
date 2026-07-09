extern void func_ov008_02050cd4(void);
extern void func_ov008_02069eec(void);
extern void func_02033b78(int, int);
extern void func_ov008_02050970(int, int);
void func_ov008_0206ab30(void)
{
    int mode = 0;
    func_ov008_02050cd4();
    func_ov008_02069eec();
    func_02033b78(0, 1);
    func_ov008_02050970(mode, mode - 1);
}
