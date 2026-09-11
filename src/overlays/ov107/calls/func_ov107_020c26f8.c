typedef void (*Callback)(void *self, int param);

typedef struct {
    unsigned bit0 : 1;
    unsigned enabled : 1;   /* bit 1 */
    unsigned rest : 30;
} Flags;

typedef struct {
    char pad_00[0x14];
    Callback callback;   /* +0x14 */
} Entity;

extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

void func_ov107_020c26f8(void *self, int flag)
{
    Flags *flags = (Flags *)((char *)self + 0x40);
    void *node;

    flags->enabled = flag;

    node = func_01fffd70((char *)self + 0x44);
    while (node != 0) {
        Entity *e = *(Entity **)node;
        if (e->callback) {
            e->callback(e, flag);
        }
        node = func_01fffd8c((char *)self + 0x44);
    }

    flags->enabled = flag;
}
