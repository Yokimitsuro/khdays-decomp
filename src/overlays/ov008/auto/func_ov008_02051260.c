extern int data_ov008_02090f04[];
void func_ov008_02051260(int index, int value)
{
    *(int *)(data_ov008_02090f04[1] + index * 4 + 0x9758) = value;
}
