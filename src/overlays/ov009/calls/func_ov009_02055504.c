/* Walk the +0x18 list, running func_ov009_02055078 on each node then removing and freeing it. */
extern void *NNS_FndGetNextListObject(void *list, void *obj);
extern void func_ov009_02055078(int node);
extern void NNS_FndRemoveListObject(void *list, void *obj);
extern void NNSi_FndFreeFromDefaultHeap(void *obj);
void func_ov009_02055504(int param_1) {
    void *node = NNS_FndGetNextListObject((void *)(param_1 + 0x18), 0);
    while (node != 0) {
        void *next = NNS_FndGetNextListObject((void *)(param_1 + 0x18), node);
        func_ov009_02055078((int)node);
        NNS_FndRemoveListObject((void *)(param_1 + 0x18), node);
        if (node != 0) NNSi_FndFreeFromDefaultHeap(node);
        node = next;
    }
}
