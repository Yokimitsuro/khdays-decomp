struct Inner {
    unsigned int b0 : 2;
    unsigned int flag : 1;
    unsigned int rest : 29;
    char pad[0x8c - 4];
};

void func_02032710(int *base, int index, int value) {
    struct Inner *p;
    if (index < 0) return;
    p = (struct Inner *)((char *)base + 0x7c);
    p[index].flag = (value != 0);
}
