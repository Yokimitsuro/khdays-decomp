extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);

struct Node { char _0[8]; void *parent; };
struct Parent { char _0[0x11c]; int count; };

void *func_0201d308(void *list) {
    int mask;
    struct Node *p;
    mask = OS_DisableInterrupts();
    p = NNS_FndGetNextListObject(list, 0);
    if (p) {
        NNS_FndRemoveListObject(list, p);
        ((struct Parent *)p->parent)->count--;
    }
    OS_RestoreInterrupts(mask);
    return p;
}
