extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern void func_0201a070(void *p);
extern void func_0201a76c(void *obj);
extern void *func_0201a7a4(int priority);
extern void func_0201a6c8(void *list, void *obj);

typedef struct Group {
    char _0[8];
    unsigned short count;
    char _a[0xe];
    unsigned int max;
    char _1c[8];
} Group;

typedef struct Obj {
    void *back;
    char _4[0x39];
    unsigned char priority;
} Obj;

typedef struct Handle {
    Obj *obj;
} Handle;

extern Group data_0204a760[];

Obj *func_0201a4c4(Handle *handle, int group_idx, int priority)
{
    Group *group = &data_0204a760[group_idx];
    Obj *new_obj;

    if (handle->obj != 0)
        func_0201a070(handle);

    if (group->count >= group->max) {
        Obj *old = (Obj *)NNS_FndGetNextListObject(group, 0);
        if (old == 0)
            return 0;
        if (priority < old->priority)
            return 0;
        func_0201a76c(old);
    }

    new_obj = (Obj *)func_0201a7a4(priority);
    if (new_obj == 0)
        return 0;

    func_0201a6c8(group, new_obj);
    new_obj->back = handle;
    handle->obj = new_obj;
    return new_obj;
}
