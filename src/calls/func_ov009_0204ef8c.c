extern int *NNS_FndGetNextListObject();
extern void NNS_FndAppendListObject();
extern void *func_02023660();

typedef struct Node {
    int field0;
    int field4;
    int field8;
    int field12;
} Node;

typedef struct Obj {
    int pad0[8];
    int list32;
} Obj;

void func_ov009_0204ef8c(Obj *obj, int key, int amt, int flag) {
    Node *node;

    node = (Node *)NNS_FndGetNextListObject(&obj->list32, 0);
    if (node != 0) {
        for (;;) {
            if (node->field0 == key) {
                node->field4 += amt;
                node->field8 |= flag;
                break;
            }
            node = (Node *)NNS_FndGetNextListObject(&obj->list32, node);
            if (node == 0) {
                break;
            }
        }
    }

    if (node != 0) {
        return;
    }

    node = (Node *)func_02023660(28);
    node->field0 = key;
    node->field4 = amt;
    node->field8 = flag;
    node->field12 = 0;
    NNS_FndAppendListObject(&obj->list32, node);
}
