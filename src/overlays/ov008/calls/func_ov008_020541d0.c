/* Walk the +0x4a38 list, invoking 02055544 on each node. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov008_02054158(int self, int node);
void func_ov008_020541d0(int param_1) {
    void *node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), 0);
    while (node != 0) {
        func_ov008_02054158(param_1, (int)node);
        node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), node);
    }
}
