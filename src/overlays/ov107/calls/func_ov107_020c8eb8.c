typedef struct {
    char pad0[4];
    int f4;
    char pad1[0x1d8 - 8];
    void *f1d8;
} Elem;

typedef struct {
    char pad[4];
    int container;
} Owner;

extern int func_01fffd70(void *o);
extern int func_01fffd8c(void *o);
extern int func_ov107_020c3504(void *p, void *source, int flag);

int func_ov107_020c8eb8(Owner *owner, void *source, void **results)
{
    int count = 0;
    void *list = (void *)(owner->container + 0xa8);
    int *it;
    Elem *elem;

    it = (int *)func_01fffd70(list);
    elem = !it ? 0 : *(Elem **)it;

    while (elem != 0) {
        if (elem->f4 == owner->container) {
            if (func_ov107_020c3504(elem->f1d8, source, 0) != 0) {
                results[count] = elem;
                count++;
            }
        }
        it = (int *)func_01fffd8c(list);
        elem = !it ? 0 : *(Elem **)it;
    }

    return count;
}
