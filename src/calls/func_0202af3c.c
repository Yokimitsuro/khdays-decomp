extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);
extern void func_0202a6d8(void *p);
extern void func_0201f924(void *dst, void *src);
extern int func_02016f10(void *p, void *q);

extern char data_0204c1f8[];

void func_0202af3c(void *a0, void *a1, void *a2) {
    int r;
    void *p;

    if (((void **)a0)[0xbc / 4] != (void *)0) {
        func_0202a6d8(a0);
    }
    if (a1 == (void *)0) return;

    INITi_CpuClear32_0x01ff86fc(0, data_0204c1f8, 0x10);
    func_0201f924(data_0204c1f8, a2);

    p = ((void **)a1)[0x24 / 4];
    p = p ? (void *)((char *)p + 0x40) : (void *)0;
    if (p == (void *)0) {
        r = -1;
    } else {
        r = func_02016f10(p, data_0204c1f8);
    }
    *(unsigned short *)((char *)a0 + 0xc8) = (unsigned short)r;

    {
        void *q = ((void **)a1)[0xc0 / 4];
        if (q != (void *)0) ((void **)a0)[0xc4 / 4] = q;
    }
    ((void **)a1)[0xc0 / 4] = a0;
    ((void **)a0)[0xbc / 4] = a1;
}
