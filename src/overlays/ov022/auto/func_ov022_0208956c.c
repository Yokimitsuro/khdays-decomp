void func_ov022_0208956c(int p, int a, int v)
{
    int base = *(int *)(p + 0x20);
    if (a >= 0) {
        *(int *)(base + 0x10) = v;
        *(int *)(base + 0x14) = v;
        *(int *)(base + 0x18) = v;
    }
}
