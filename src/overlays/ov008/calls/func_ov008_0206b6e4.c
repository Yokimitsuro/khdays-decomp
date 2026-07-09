extern int func_ov008_0206b7f8(void);
extern unsigned char data_ov008_0208f852[];

int func_ov008_0206b6e4(void)
{
    int index = func_ov008_0206b7f8();

    if (index < 0) {
        return 0;
    }

    if (index >= 0x14) {
        return 0;
    }

    return *(unsigned short *)(data_ov008_0208f852 + index * 6);
}
