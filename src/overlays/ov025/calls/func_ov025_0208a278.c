/* Search the linked list at param_1+0x18 for the first object whose u16 id at
 * +2 equals param_2; return it, or NULL. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);

void *func_ov025_0208a278(int param_1, int param_2) {
    void *obj = NNS_FndGetNextListObject((void *)(param_1 + 0x18), 0);
    while (obj != 0) {
        if (*(unsigned short *)((char *)obj + 2) == param_2) {
            break;
        }
        obj = NNS_FndGetNextListObject((void *)(param_1 + 0x18), obj);
    }
    return obj;
}
