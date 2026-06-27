extern void *NNS_FndGetNextListObject(void *list, void *object);
extern void func_020300f8(void *p);

typedef struct {
    char _0[0x18];
    void *current;
    void *currentData;
    char _20[0xc];
    char list[0x10];
} X02030094;

void func_02030094(X02030094 *p, void *target, int update)
{
    void *cur = NNS_FndGetNextListObject(p->list, 0);

    if (target != 0 && cur != 0) {
        for (;;) {
            if (cur == target)
                break;
            cur = NNS_FndGetNextListObject(p->list, cur);
            if (cur == 0)
                break;
        }
    }

    p->currentData = (char *)cur + 8;
    p->current = cur;

    if (update != 0)
        func_020300f8(p);
}
