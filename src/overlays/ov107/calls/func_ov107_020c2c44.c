extern int func_01fffd70(void *o);
extern int func_01fffd8c(void *o);
extern void NNSi_FndDestroyDoubleList(void *list);
extern void func_ov107_020c0d74(void *obj);

void func_ov107_020c2c44(char *self)
{
    void *list = self + 0x44;
    int *it;

    for (it = (int *)func_01fffd70(list); it != 0; it = (int *)func_01fffd8c(list)) {
        void *elem = *(void **)it;
        void (*cb)(void *) = *(void (**)(void *))((char *)elem + 8);
        if (cb != 0) {
            cb(elem);
        }
    }

    NNSi_FndDestroyDoubleList(list);
    func_ov107_020c0d74(self);
}
