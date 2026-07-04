int func_ov022_020954c0(int p)
{
    if (*(int *)(p + 4) == 8) {
        if (*(int *)p & 0x80)
            return 1;
    }
    return 0;
}
