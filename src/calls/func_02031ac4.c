struct Entry02031ac4 {
    unsigned int bit0 : 1;
    unsigned int _rest : 31;
    char _4[0x8c - 4];
};

int func_02031ac4(char *base)
{
    struct Entry02031ac4 *p = (struct Entry02031ac4 *)(base + 0x7c);
    int i = 0;
    do {
        if (p->bit0 == 0) return i;
        i++;
        p = (struct Entry02031ac4 *)((char *)p + 0x8c);
    } while (i < 0x80);
    return -1;
}
