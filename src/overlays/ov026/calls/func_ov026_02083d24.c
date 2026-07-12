/* Walk the +0x4a38 list, invoking 02055544 on each node. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov026_02083cac(int self, int node);
void func_ov026_02083d24(int param_1) {
    void *node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), 0);
    while (node != 0) {
        func_ov026_02083cac(param_1, (int)node);
        node = NNS_FndGetNextListObject((void *)(param_1 + 0x4a38), node);
    }
}
