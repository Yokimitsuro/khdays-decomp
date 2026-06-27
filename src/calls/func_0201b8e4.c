extern void *NNS_FndGetPrevListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void func_02010c00(int heap, int flags);
extern int func_0201bb6c(void *p);
extern void func_0201bba8(void);

typedef struct {
    int heap;
    char list[0x10];
} Obj;

typedef struct {
    int pad0[2];
    int field8;
    void (*fieldC)(void *data, int field8, int field10, int field14);
    int field10;
    int field14;
} Node;

void func_0201b8e4(Obj *p)
{
    void *outer;
    int flag;
    Node *inner;

    flag = 0;
    outer = NNS_FndGetPrevListObject(&p->list, flag);
    if (outer != 0) {
        do {
            inner = (Node *)NNS_FndGetPrevListObject(outer, 0);
            while (inner != 0) {
                if (inner->fieldC != 0) {
                    inner->fieldC((char *)inner + 0x20, inner->field8, inner->field10, inner->field14);
                    flag = 1;
                }
                inner = (Node *)NNS_FndGetPrevListObject(outer, inner);
            }
            NNS_FndRemoveListObject(&p->list, outer);
            outer = NNS_FndGetPrevListObject(&p->list, 0);
        } while (outer != 0);
    }

    func_02010c00(p->heap, 3);
    if (flag != 0)
        func_0201bba8();
    func_0201bb6c(p);
}
