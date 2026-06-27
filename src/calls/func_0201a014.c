extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void func_0201a604(void *p, int flag);

extern char data_0204a314[];

void func_0201a014(int flag)
{
    void *obj = NNS_FndGetNextListObject(data_0204a314, 0);

    if (obj == 0)
        return;

    do {
        void *next = NNS_FndGetNextListObject(data_0204a314, obj);

        func_0201a604(obj, flag);
        obj = next;
    } while (obj != 0);
}
