extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void NNS_FndInsertListObject(void *list, void *target, void *object);

extern char data_0204a314[];

struct Obj { char _0[0x3d]; unsigned char priority; };

void func_0201a718(struct Obj *new_obj) {
    struct Obj *cur = (struct Obj *)NNS_FndGetNextListObject(data_0204a314, 0);
    while (cur != 0) {
        if (new_obj->priority < cur->priority) break;
        cur = (struct Obj *)NNS_FndGetNextListObject(data_0204a314, cur);
    }
    NNS_FndInsertListObject(data_0204a314, cur, new_obj);
}
