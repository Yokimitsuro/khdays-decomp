int func_0200ff54(int p)
{
    int len = 0;
    if (*(signed char *)p != 0) {
        do {
            len++;
        } while (*(signed char *)(p + len) != 0);
    }
    return len;
}
