/* Walk the +0x4a38 list, invoking func_ov005_0204e018 on each node (advancing safely first). */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov005_0204e018(int, void *);
void func_ov005_0204e064(int param_1) {
    void *node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), 0);
    while (node != 0) {
        void *next = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), node);
        func_ov005_0204e018(param_1, node);
        node = next;
    }
}
