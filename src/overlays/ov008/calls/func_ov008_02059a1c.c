extern void func_ov008_02050e2c(int arg0);
extern void func_ov008_02050fe0(int arg0);
extern void func_ov008_02051010(int arg0);
extern void func_ov008_02050970(int arg0, int arg1);
extern void func_02033b78(int arg0, int arg1);

void func_ov008_02059a1c(void)
{
    int value = 1;

    func_ov008_02050e2c(0);
    func_ov008_02050fe0(value);
    func_ov008_02051010(value);
    func_ov008_02050970(value, value - 2);
    func_02033b78(0, value);
}
