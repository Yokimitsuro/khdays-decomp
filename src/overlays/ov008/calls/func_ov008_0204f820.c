extern char *data_ov008_02090f04[];
extern void func_ov008_0204f2a8(void);
extern void func_ov008_020513f0(int arg0);
extern void func_ov008_020514cc(int arg0);

void func_ov008_0204f820(void)
{
    func_ov008_0204f2a8();
    func_ov008_020513f0(*(int *)(data_ov008_02090f04[1] + 0x959c));
    func_ov008_020514cc(*(int *)(data_ov008_02090f04[1] + 0x95a0));
}
