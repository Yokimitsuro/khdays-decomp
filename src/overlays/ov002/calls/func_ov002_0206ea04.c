/* Recursively tear down a node: free the child at +0x18, run the destructor at +4
 * (if any), then free the node itself. */
extern void NNSi_FndFreeFromDefaultHeap(void *p);

void func_ov002_0206ea04(int param_1) {
    void (*dtor)(int);

    if (*(int *)(param_1 + 0x18) != 0) {
        func_ov002_0206ea04(*(int *)(param_1 + 0x18));
    }
    dtor = *(void (**)(int))(param_1 + 4);
    if (dtor != 0) {
        dtor(param_1);
    }
    NNSi_FndFreeFromDefaultHeap((void *)param_1);
}
