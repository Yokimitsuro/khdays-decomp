struct dev {
    unsigned char _pad[0x4a7c];
    unsigned int enable : 1;
};

void func_ov008_02054e24(int base, int flag)
{
    ((struct dev *)base)->enable = (flag != 0);
}
