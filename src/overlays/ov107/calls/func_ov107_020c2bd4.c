extern void *func_01fffd70(void *list);
extern int func_01fffd0c(void *list, void *handle);
extern void *func_01fffd8c(void *list);

typedef void (*Callback)(void *target, void *self);

typedef struct Target {
    void *field_00;
    int field_04;
    char pad_08[0x2c - 0x08];
    Callback field_2c;
} Target;

void func_ov107_020c2bd4(void *self, Target *target)
{
    void *list;
    void *handle;

    if (target == 0) {
        return;
    }

    list = (char *)self + 0x44;
    handle = func_01fffd70(list);
    if (handle == 0) {
        return;
    }

    for (;;) {
        if (*(Target **)handle == target) {
            target->field_04 = 0;
            if (target->field_2c != 0) {
                target->field_2c(target, self);
            }
            func_01fffd0c(list, handle);
            return;
        }
        handle = func_01fffd8c(list);
        if (handle == 0) {
            return;
        }
    }
}
