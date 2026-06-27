extern int func_0201b8cc(void *p);
extern void NNS_FndRemoveListObject(void *list, void *object);

extern char data_0204a760[];

typedef struct Obj0201a890 {
    char _0[8];
    void *active;
    struct Obj0201a890 *parent;
    int index;
} Obj0201a890;

void func_0201a890(Obj0201a890 *obj)
{
    if (obj->active == 0)
        return;

    func_0201b8cc(obj->active);

    if (obj->parent != 0) {
        obj->parent->active = 0;
        return;
    }

    NNS_FndRemoveListObject(data_0204a760 + obj->index * 0x24 + 0xc, obj);
}
