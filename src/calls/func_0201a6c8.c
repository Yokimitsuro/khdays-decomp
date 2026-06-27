extern void *NNS_FndGetNextListObject();
extern void NNS_FndInsertListObject();

struct Obj {
    char _0[4];
    void *list_back;
    char _8[0x35];
    unsigned char priority;
};

void func_0201a6c8(void *list, struct Obj *new_obj) {
    struct Obj *cur = NNS_FndGetNextListObject(list, 0);
    while (cur != 0) {
        if (new_obj->priority < cur->priority) break;
        cur = NNS_FndGetNextListObject(list, cur);
    }
    NNS_FndInsertListObject(list, cur, new_obj);
    new_obj->list_back = list;
}
