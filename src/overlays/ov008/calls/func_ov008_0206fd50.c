/* Search the linked list at param_1+0x4d4 for the first object whose u16 id at
 * +0 equals param_2; return it, or NULL. */
extern void *func_ov008_020565bc(void *list, void *obj);

void *func_ov008_0206fd50(int param_1, int param_2) {
    void *obj = func_ov008_020565bc((void *)(param_1 + 0x4d4), 0);
    while (obj != 0) {
        if (*(unsigned short *)obj == param_2) {
            return obj;
        }
        obj = func_ov008_020565bc((void *)(param_1 + 0x4d4), obj);
    }
    return obj;
}
