extern int func_02020e58(int);
extern int func_0201e428(int);
extern char *data_ov023_0208a784;

int func_ov023_02083ad0(void)
{
    int r;
    r = func_02020e58((int)((&data_ov023_0208a784)[1] + 0x4b88));
    r = func_0201e428(r);
    if (r == ~0xf) return 1;
    return 0;
}
