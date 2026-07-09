extern volatile int data_ov008_02090f04[];
void func_ov008_02051040(int x, int y)
{
    *(unsigned short *)(data_ov008_02090f04[1] + 0x9638) = x;
    *(unsigned short *)(data_ov008_02090f04[1] + 0x963a) = y;
}
