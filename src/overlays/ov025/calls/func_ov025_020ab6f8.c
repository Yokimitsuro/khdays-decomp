/* Twin of func_ov008_0206fd50 for the linked list at param_1+0x548. */
extern void *func_ov025_0208a1cc(void *list, void *obj);

void *func_ov025_020ab6f8(int param_1, int param_2) {
    void *obj = func_ov025_0208a1cc((void *)(param_1 + 0x548), 0);
    while (obj != 0) {
        if (*(unsigned short *)obj == param_2) {
            return obj;
        }
        obj = func_ov025_0208a1cc((void *)(param_1 + 0x548), obj);
    }
    return obj;
}
