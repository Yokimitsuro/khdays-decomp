/* Walk the +0x4a38 list, invoking func_ov000_02055a8c on each node (advancing safely first). */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov000_02055a8c(int, void *);
void func_ov000_02055ad8(int param_1) {
    void *node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), 0);
    while (node != 0) {
        void *next = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), node);
        func_ov000_02055a8c(param_1, node);
        node = next;
    }
}
