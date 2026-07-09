extern int data_ov008_02090f24[];
extern void func_ov105_020bf8c8(int arg0);
extern void func_02023a44(int arg0, void (*callback)(void));
extern void func_ov105_020bf928(void);
extern void func_ov008_0207ab10(void);

void func_ov008_0207bb90(void)
{
    func_ov105_020bf8c8(0);
    func_02023a44(data_ov008_02090f24[1], func_ov008_0207ab10);
    func_ov105_020bf928();
}
