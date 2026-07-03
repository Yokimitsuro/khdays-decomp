struct dev { unsigned char _pad[0x4a7c]; unsigned int bit0 : 1, bit1 : 1; };
void func_ov009_02051c30(int base, int flag)
{
    ((struct dev *)base)->bit1 = (flag != 0);
}
