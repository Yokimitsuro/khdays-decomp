extern void *NNS_FndAllocFromExpHeapEx_0x02010bcc(int heap, unsigned int size, unsigned int align);
extern void *NNS_FndGetPrevListObject(void *list, void *object);
extern void NNS_FndAppendListObject(void *list, void *object);

typedef struct {
    int heap;
    char list[0x10];
} Obj;

typedef struct {
    int pad0[2];
    int field8;
    int fieldC;
    int field10;
    int field14;
} Node;

void *func_0201b9a0(Obj *obj, unsigned int size, int a2, int a3, int a4)
{
    Node *node;

    node = (Node *)NNS_FndAllocFromExpHeapEx_0x02010bcc(obj->heap, ((size + 0x1f) & ~0x1f) + 0x20, 0x20);
    if (node == 0) {
        return 0;
    }

    {
        void *prev = NNS_FndGetPrevListObject(&obj->list, 0);
        node->field8  = size;
        node->fieldC  = a2;
        node->field10 = a3;
        node->field14 = a4;
        NNS_FndAppendListObject(prev, node);
    }

    return (char *)node + 0x20;
}
