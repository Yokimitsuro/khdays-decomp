struct dev { unsigned char _pad[0x4a7c]; unsigned int bit0 : 1, bit1 : 1; };
void func_ov025_02088af4(int base, int flag)
{
    ((struct dev *)base)->bit1 = (flag != 0);
}
