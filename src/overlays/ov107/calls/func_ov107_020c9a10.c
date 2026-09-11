typedef struct { void *f0; void *f4; void *f8; } Step;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_02024fd4(void *p);
extern void func_0203d194(void *p);
extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_ov107_020c2f40(void);
extern void func_02030d10(int a);

extern void *data_ov107_020cbf1c;

void func_ov107_020c9a10(void) {
    char *root;
    int i;
    char *p;
    void **node;

    root = (char *)NNSi_FndGetCurrentRootHeap();
    i = 0;
    p = root;
    for (; i < 4; i++) {
        Step *s = *(Step **)(p + 0x2c);
        if (s->f4 == 0 && s->f8 != 0) {
            ((void (*)(Step *))s->f8)(s);
        }
        p += 4;
    }
    func_02024fd4(*(void **)(root + 0x7c));
    func_02024fd4(*(void **)(root + 0x80));
    func_02024fd4(*(void **)(root + 0x84));
    func_02024fd4(*(void **)(root + 0x88));
    {
        Step *v = *(Step **)root;
        if (v->f8 != 0) {
            ((void (*)(Step *))v->f8)(v);
        }
    }
    node = (void **)func_01fffd70(root + 0x4c);
    while (node != 0) {
        func_02024fd4(node[0]);
        func_0203d194(node[1]);
        node = (void **)func_01fffd8c(root + 0x4c);
    }
    NNSi_FndDestroyDoubleList(root + 0x4c);
    NNSi_FndDestroyDoubleList(root + 4);
    if (*(void **)(root + 0x48) != 0) {
        func_0203d194(*(void **)(root + 0x48));
    }
    *(int *)(root + 0x48) = 0;
    func_ov107_020c2f40();
    func_02030d10(1);
    func_02030d10(4);
    data_ov107_020cbf1c = 0;
}
