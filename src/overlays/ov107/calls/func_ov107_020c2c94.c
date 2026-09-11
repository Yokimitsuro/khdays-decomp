typedef void (*Callback)(void *self, void *param);

typedef struct {
    char pad_00[0xc];
    Callback callback;   /* +0xc */
    char pad_10[0x40 - 0xc - 4];
    int flags;            /* +0x40 */
} Entity;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

void func_ov107_020c2c94(void *obj, void *param1) {
    void *node = func_01fffd70((char *)obj + 0x44);
    while (node != 0) {
        Entity *e = *(Entity **)node;
        int flag = (e->flags << 30) >> 31;
        if (flag) {
            if (flag && e->callback) {
                e->callback(e, param1);
            }
        }
        node = func_01fffd8c((char *)obj + 0x44);
    }
}
