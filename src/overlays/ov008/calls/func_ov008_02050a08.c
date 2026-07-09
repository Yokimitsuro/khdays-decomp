extern char *data_ov008_02090f04[];
extern void func_ov008_0204ee28(int arg0);
extern void func_ov008_0204eff0(int arg0, int arg1);
extern void func_ov008_0204f1ac(int arg0);

void func_ov008_02050a08(int value)
{
    *(int *)(data_ov008_02090f04[1] + 0x95c8) = value;
    func_ov008_0204ee28(7);
    func_ov008_0204eff0(-0x10, 0x64);
    func_ov008_0204f1ac(0);
}
