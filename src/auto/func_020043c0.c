int func_020043c0(int value, int *ptr)
{
    int old;
    __asm
    {
        swp old, value, [ptr]
    }
    return old;
}
