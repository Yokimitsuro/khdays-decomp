typedef void (*Callback)(void *self, int param);

typedef struct {
    signed int flag0 : 1;   /* bit0 */
    signed int flag1 : 1;   /* bit1 */
    signed int flag2 : 1;   /* bit2 */
    signed int rest  : 29;
} Flags;

typedef struct {
    char pad_00[0x10];
    Callback cb;             /* +0x10 */
    char pad_14[0x40 - 0x14];
    Flags flags;              /* +0x40 */
} Entity;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

void func_ov107_020c2cec(void *self)
{
    void *node = func_01fffd70((char *)self + 0x44);
    if (node == 0) return;

    do {
        Entity *e = *(Entity **)node;
        if (e->flags.flag1) {
            if (!e->flags.flag0) {
                if (e->flags.flag2) {
                    if (e->cb) e->cb(e, 1);
                }
            } else {
                if (e->flags.flag0) {
                    if (e->flags.flag2) {
                        if (e->cb) e->cb(e, 0);
                    }
                }
            }
        }
        node = func_01fffd8c((char *)self + 0x44);
    } while (node != 0);
}
