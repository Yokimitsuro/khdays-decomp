extern int data_ov008_02090f1c;

/* Clear DISPCNT display-mode bits 13-15 (blank the 2D engine A output). */
void func_ov008_02058a04(void)
{
    volatile unsigned int *reg_dispcnt = (volatile unsigned int *)0x04000000;
    *reg_dispcnt &= ~0xe000;
    data_ov008_02090f1c = 0;
}
