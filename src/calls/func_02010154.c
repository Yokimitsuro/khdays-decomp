extern void *NNS_FndGetNextListObject(void *list, void *prev);

void *func_02010154(void *list, int target_idx) {
    int i = 0;
    void *obj = NNS_FndGetNextListObject(list, 0);
    while (obj != 0) {
        if (i == target_idx) return obj;
        i++;
        obj = NNS_FndGetNextListObject(list, obj);
    }
    return 0;
}
