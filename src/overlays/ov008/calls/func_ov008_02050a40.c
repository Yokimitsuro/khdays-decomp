extern void func_ov008_0204f1ac(void);
extern int data_ov008_02090f04[];
void func_ov008_02050a40(int value)
{
    func_ov008_0204f1ac();
    *(int *)(data_ov008_02090f04[1] + 0x95fc) = value;
}
