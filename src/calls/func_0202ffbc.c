extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void NNSi_FndFreeFromDefaultHeap(void *p);

typedef struct {
    char _00[0x20];
    void *sub;
    char _24[0x2c - 0x24];
    char list[0x10];
} Obj0202ffbc;

void func_0202ffbc(Obj0202ffbc *self)
{
    void *next;
    void *obj;
    void *zero = 0;

    obj = NNS_FndGetNextListObject(&self->list, 0);
    if (obj == 0)
        return;

    do {
        next = NNS_FndGetNextListObject(&self->list, obj);

        if (((Obj0202ffbc *)obj)->sub != 0) {
            NNSi_FndFreeFromDefaultHeap(((Obj0202ffbc *)obj)->sub);
            ((Obj0202ffbc *)obj)->sub = zero;
        }
        if (obj != 0) {
            NNSi_FndFreeFromDefaultHeap(obj);
        }
        obj = next;
    } while (next != 0);
}
