/* In the list at param_1+0x300, find the object seeded by func_02010154(param_2)
 * whose linked record's field at +0x14 equals param_3; return it, or NULL. */
extern void *func_02010154(void *list, int key);
extern void *NNS_FndGetNextListObject(void *list, void *obj);

void *func_ov025_02090580(int param_1, int param_2, int param_3) {
    void *obj = func_02010154(*(void **)(param_1 + 0x300), (unsigned short)param_2);
    while (obj != 0) {
        if (*(int *)(*(int *)obj + 0x14) == param_3) {
            break;
        }
        obj = NNS_FndGetNextListObject(*(void **)(param_1 + 0x300), obj);
    }
    return obj;
}
