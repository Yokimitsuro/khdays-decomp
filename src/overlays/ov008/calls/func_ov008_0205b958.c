extern char *func_ov008_02050cd4(void);

int func_ov008_0205b958(int offset)
{
    return (unsigned char)*(func_ov008_02050cd4() + offset + 0x14f0);
}
