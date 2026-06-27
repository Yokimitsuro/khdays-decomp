extern void *func_0201b9a0(void *obj, unsigned int size, void *fn, int a3, int a4);
extern void *func_0201b85c(unsigned int start, unsigned int size);
extern void NNS_FndAppendListObject(void *list, void *object);

extern void func_0201a890(void);
extern char data_0204a760[];

void *func_02019e08(int a0, void *a1, unsigned int a2)
{
    void *p;
    void *q;

    p = func_0201b9a0(a1, a2 + 0x14, (void *)func_0201a890, 0, 0);
    if (p == 0) {
        return 0;
    }

    *((int *)p + 3) = 0;
    *((int *)p + 4) = a0;
    *((int *)p + 2) = 0;
    q = func_0201b85c((unsigned int)((char *)p + 0x14), a2);
    if (q == 0) {
        return 0;
    }

    *((int *)p + 2) = (int)q;
    NNS_FndAppendListObject(data_0204a760 + a0 * 0x24 + 0xc, p);
    return (void *)1;
}
