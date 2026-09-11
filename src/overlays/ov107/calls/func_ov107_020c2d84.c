typedef struct HandlerObj {
    char pad[0x20];
    void (*handler)(struct HandlerObj *self);
} HandlerObj;

typedef HandlerObj **ListItem;

typedef struct Ov107 {
    char pad[0x6c];
    int field_6c;
} Ov107;

extern ListItem func_01fffd70(void *list);
extern ListItem func_01fffd8c(void *list);
extern ListItem func_01fffdac(void *list);
extern ListItem func_01fffdc4(void *list);

void func_ov107_020c2d84(Ov107 *self)
{
    void *list = (char *)self + 0x44;
    ListItem item;

    self->field_6c++;
    if (self->field_6c & 1) {
        item = func_01fffd70(list);
        if (item != 0) {
            do {
                HandlerObj *obj = *item;
                if (obj->handler) {
                    obj->handler(obj);
                }
                item = func_01fffd8c(list);
            } while (item != 0);
        }
    } else {
        item = func_01fffdac(list);
        if (item != 0) {
            do {
                HandlerObj *obj = *item;
                if (obj->handler) {
                    obj->handler(obj);
                }
                item = func_01fffdc4(list);
            } while (item != 0);
        }
    }
}
