extern int data_ov008_02090f24[];
extern void func_ov105_020bf8c8(int arg0);
extern void func_02023a44(int arg0, void (*callback)(void));
extern void func_ov008_02079a20(void);
extern void func_ov008_0207aad8(void);

void func_ov008_0207bb4c(void)
{
    func_ov105_020bf8c8(0);
    func_02023a44(data_ov008_02090f24[1], func_ov008_0207aad8);
    func_ov008_02079a20();
}
