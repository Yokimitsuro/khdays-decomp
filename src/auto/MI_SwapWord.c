int MI_SwapWord(int value, int *ptr)
{
    int old;
    __asm
    {
        swp old, value, [ptr]
    }
    return old;
}
