/* Teardown: run func_ov002_02054984, then free the +0x14/+0x10/+0xc sub-allocations if present. */
extern void func_ov002_02054984(int);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void func_ov002_02054458(int param_1) {
    void *p;
    func_ov002_02054984(param_1);
    p = *(void **)(param_1 + 0x14); if (p != 0) NNSi_FndFreeFromDefaultHeap(p);
    p = *(void **)(param_1 + 0x10); if (p != 0) NNSi_FndFreeFromDefaultHeap(p);
    p = *(void **)(param_1 + 0xc); if (p != 0) NNSi_FndFreeFromDefaultHeap(p);
}
