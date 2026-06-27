extern int OS_DisableInterrupts();
extern void OS_RestoreInterrupts(int mask);
extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void func_0201d398(void *object);

struct Node { char _0[8]; void *parent; };

void func_0201d298(void *list, void *parent) {
    int mask;
    struct Node *p;
    struct Node *next;
    mask = OS_DisableInterrupts();
    p = NNS_FndGetNextListObject(list, 0);
    if (p) {
        do {
            next = NNS_FndGetNextListObject(list, p);
            if (p->parent == parent) {
                NNS_FndRemoveListObject(list, p);
                func_0201d398(p);
            }
            p = next;
        } while (next);
    }
    OS_RestoreInterrupts(mask);
}
