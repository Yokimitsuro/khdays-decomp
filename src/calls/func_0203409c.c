extern int func_0201cb3c(void *a0, unsigned int a1, int a2);
extern unsigned char *data_0204c234;

int func_0203409c(int arg0, int arg1)
{
    unsigned char *base = data_0204c234;
    return func_0201cb3c(base + 0xb44bc + arg0 * 4, base[0xb47b7], arg1);
}
