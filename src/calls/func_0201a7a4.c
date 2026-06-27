typedef struct {
    char _0[0x3d];
    unsigned char priority;
} Obj0201a7a4;

extern Obj0201a7a4 *NNS_FndGetNextListObject(void *list, void *prev);
extern void NNS_FndRemoveListObject(void *list, Obj0201a7a4 *object);
extern void func_0201a76c(Obj0201a7a4 *object);
extern void func_0201a718(Obj0201a7a4 *object);

extern char data_0204a308[];
extern char data_0204a314[];

Obj0201a7a4 *func_0201a7a4(int priority)
{
    Obj0201a7a4 *obj = NNS_FndGetNextListObject(data_0204a308, 0);

    if (obj == 0) {
        obj = NNS_FndGetNextListObject(data_0204a314, 0);

        if (priority < obj->priority)
            return 0;

        func_0201a76c(obj);
    }

    NNS_FndRemoveListObject(data_0204a308, obj);
    obj->priority = priority;
    func_0201a718(obj);

    return obj;
}
