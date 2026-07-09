extern int data_ov008_02090f1c;
void func_ov008_02058a04(void)
{
    *(volatile unsigned int *)0x04000000 &= ~0xe000;
    data_ov008_02090f1c = 0;
}
