extern void func_02032450(void *p, int idx);

void func_02032494(void *p)
{
    int i;
    for (i = 0; i < 0x80; i++) {
        func_02032450(p, i);
    }
}
