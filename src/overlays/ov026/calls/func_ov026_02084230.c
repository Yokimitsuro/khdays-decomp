/* Walk the +0x4a38 list, invoking func_ov026_020841e4 on each node (advancing safely first). */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov026_020841e4(int, void *);
void func_ov026_02084230(int param_1) {
    void *node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), 0);
    while (node != 0) {
        void *next = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), node);
        func_ov026_020841e4(param_1, node);
        node = next;
    }
}
