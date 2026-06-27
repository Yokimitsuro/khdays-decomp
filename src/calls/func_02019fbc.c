extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void func_0201a604(void *p, int flag);

extern char data_0204a760[];

void func_02019fbc(int index, int flag)
{
    int offset = index * 0x24;
    void *obj = NNS_FndGetNextListObject(data_0204a760 + offset, 0);

    if (obj == 0)
        return;

    do {
        void *next = NNS_FndGetNextListObject(data_0204a760 + offset, obj);

        func_0201a604(obj, flag);
        obj = next;
    } while (obj != 0);
}
