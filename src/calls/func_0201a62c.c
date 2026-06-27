extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNS_FndRemoveListObject(void *list, void *object);
extern void func_0201b8e4(void *p);

extern char data_0204a760[];

typedef struct Obj0201a62c {
    char _0[8];
    void *active;
    struct Obj0201a62c *parent;
} Obj0201a62c;

void *func_0201a62c(int index, Obj0201a62c *parent)
{
    char *entry = data_0204a760 + index * 0x24;
    Obj0201a62c *obj = NNS_FndGetNextListObject(entry + 0xc, 0);

    if (obj == 0)
        return 0;

    NNS_FndRemoveListObject(entry + 0xc, obj);
    obj->parent = parent;
    parent->active = obj;
    func_0201b8e4(obj->active);
    return obj->active;
}
