extern int data_ov008_02090f04[];
void func_ov008_02050ebc(int value)
{
    *(int *)(data_ov008_02090f04[1] + 0x9628) = value == 0;
}
