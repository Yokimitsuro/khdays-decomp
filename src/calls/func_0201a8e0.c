extern void NNS_FndRemoveListObject(void *list, void *object);
extern void func_0201a6c8(void *list, void *object);
extern void func_0201a718(void *object);

extern char data_0204a314[];

typedef struct {
    char _0[4];
    void *list;
    char _8[0x35];
    unsigned char priority;
} Obj0201a8e0;

void func_0201a8e0(Obj0201a8e0 *obj, unsigned char priority)
{
    void *list = obj->list;

    if (list != 0) {
        NNS_FndRemoveListObject(list, obj);
        obj->list = 0;
    }

    NNS_FndRemoveListObject(data_0204a314, obj);
    obj->priority = priority;

    if (list != 0)
        func_0201a6c8(list, obj);

    func_0201a718(obj);
}
