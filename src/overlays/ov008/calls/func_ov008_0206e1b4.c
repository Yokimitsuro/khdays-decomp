/* func_ov008_0206e1b4 -- apply func_ov008_0206e0c0 to every node in the object list at
 * param_1+0x1cc (fetching the next link before the callback, so callbacks may unlink). */
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern void func_ov008_0206e0c0(int owner, int node);

void func_ov008_0206e1b4(int param_1) {
    int node = NNS_FndGetNextListObject((void *)(param_1 + 0x1cc), 0);
    int next;
    if (node == 0) {
        return;
    }
    do {
        next = NNS_FndGetNextListObject((void *)(param_1 + 0x1cc), node);
        func_ov008_0206e0c0(param_1, node);
        node = next;
    } while (next != 0);
}
