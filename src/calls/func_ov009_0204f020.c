extern int *func_02010128();
extern void func_0200ffc0();
extern void *func_02023660();

typedef struct Node {
    int field0;
    int field4;
    int field8;
    int field12;
    int field16;
    int field20;
} Node;

typedef struct Obj {
    int pad0[2];
    int list8;
    int pad12[59];
    int (*fn248)();
    int (*fn252)();
} Obj;

void func_ov009_0204f020(Obj *obj, int key, int amt16, int amt20, int flag8) {
    Node *node;
    int tmp[1];

    tmp[0] = 0;

    node = (Node *)func_02010128(&obj->list8, 0);
    if (node != 0) {
        for (;;) {
            if (node->field0 == key) {
                node->field16 += amt16;
                node->field20 += amt20;
                node->field8 |= flag8;
                break;
            }
            node = (Node *)func_02010128(&obj->list8, node);
            if (node == 0) {
                break;
            }
        }
    }

    if (node == 0) {
        node = (Node *)func_02023660(36);
        node->field0 = key;
        node->field16 = amt16;
        node->field20 = amt20;
        node->field8 = flag8;
        node->field12 = 0;
        func_0200ffc0(&obj->list8, node, 0);
    }

    obj->fn248(tmp, 19, key, 14);
    if (node->field16 > *(unsigned char *)(tmp[0] + 36)) {
        node->field16 = *(unsigned char *)(tmp[0] + 36);
    }
    obj->fn252(tmp);
    {
        int v = node->field20;
        if (v > 99) {
            v = 99;
        }
        node->field20 = v;
    }
}
