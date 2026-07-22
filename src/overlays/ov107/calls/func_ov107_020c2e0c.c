/* func_ov107_020c2e0c -- walk the object's child list at +0x44 and run each child's +0x34 handler
 * (skipping the ones that have none). */
extern int func_01fffd70(void *list);
extern int func_01fffd8c(void *list);

void func_ov107_020c2e0c(int obj) {
    int *node;
    void (*cb)(int);
    node = (int *)func_01fffd70((void *)(obj + 0x44));
    while (node != 0) {
        cb = *(void (**)(int))(node[0] + 0x34);
        if (cb != 0) {
            cb(node[0]);
        }
        node = (int *)func_01fffd8c((void *)(obj + 0x44));
    }
}
