extern unsigned char data_ov008_0208ee84[];

int func_ov008_0205ba30(unsigned int value)
{
    unsigned short i = 0;

    do {
        if (value < *(unsigned short *)(data_ov008_0208ee84 + i * 8)) {
            return i;
        }

        i++;
    } while (i < 0x38);

    return 0;
}
