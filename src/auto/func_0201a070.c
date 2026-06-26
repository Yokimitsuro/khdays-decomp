void func_0201a070(int *volatile *p)
{
    if (*p == 0) {
        return;
    }
    **p = 0;
    *p = 0;
}
