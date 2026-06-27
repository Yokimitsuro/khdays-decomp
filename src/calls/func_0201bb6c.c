extern void *NNS_FndAllocFromExpHeapEx_0x02010bcc(int arg0, unsigned int size, unsigned int align);
extern void NNS_FndInitListWithOffset0(void *p);
extern void NNS_FndAppendListObject(void *list, void *object);

typedef struct {
    int heap;
    char list[0x10];
} X0201bb6c;

int func_0201bb6c(X0201bb6c *p)
{
    void *object = NNS_FndAllocFromExpHeapEx_0x02010bcc(p->heap, 0x14, 4);

    if (object == 0)
        return 0;

    NNS_FndInitListWithOffset0(object);
    NNS_FndAppendListObject(p->list, object);
    return 1;
}
