/* Continue walking self's object list (head at self+0x18) from `obj` and return the
 * next entry whose field_0x10 is 0, or NULL if the list ends first. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
void *func_ov025_0208a1cc(int self, void *obj) {
    obj = NNS_FndGetNextListObject((void *)(self + 0x18), obj);
    if (obj != 0) {
        do {
            if (*(int *)((char *)obj + 0x10) == 0) break;
            obj = NNS_FndGetNextListObject((void *)(self + 0x18), obj);
        } while (obj != 0);
    }
    return obj;
}
