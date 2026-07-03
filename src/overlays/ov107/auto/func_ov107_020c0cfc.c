struct b2 { unsigned int b0 : 1, b1 : 1; };
void func_ov107_020c0cfc(int p, int flag)
{
    ((struct b2 *)(p + 0x40))->b1 = flag;
}
