struct bf6 { unsigned char lo : 2, hi : 6; };
int func_ov022_02089628(int p)
{
    return ((struct bf6 *)(*(int *)(p + 0x20)))->hi;
}
