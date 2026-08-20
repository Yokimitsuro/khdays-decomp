extern int data_ov002_0207f638;

extern void func_ov002_02052af4(int pTask, int nResult);
extern int func_ov002_02052aec(int pTask);
extern void NNSi_FndFreeFromDefaultHeap(void *pBlock);
extern void func_02011988(int nHandle, int *ppInfo);
extern void DC_FlushRange(void *pAddress, int nSize);

/* Swap in a freshly loaded block for the owner: drop the old one, take the
 * task's payload, resolve it, flush it to memory and mark the slot ready. */
void func_ov002_020648ec(int pTask, int nSlot)
{
    int pOwner;

    pOwner = *(int *)&data_ov002_0207f638;
    if (pOwner == 0) {
        func_ov002_02052af4(pTask, 1);
        return;
    }

    *(unsigned char *)(pOwner + 0x28) = 0;

    if (*(void **)(pOwner + 0x2c) != 0) {
        NNSi_FndFreeFromDefaultHeap(*(void **)(pOwner + 0x2c));
        *(int *)(pOwner + 0x2c) = 0;
    }

    *(int *)(pOwner + 0x2c) = func_ov002_02052aec(pTask);
    func_02011988(*(int *)(pOwner + 0x2c), (int *)(pOwner + 0x30));
    DC_FlushRange(*(void **)(*(int *)(pOwner + 0x30) + 0x14),
                  *(int *)(*(int *)(pOwner + 0x30) + 0x10));

    *(unsigned char *)(pOwner + 0x28) = 1;
    *(unsigned char *)(pOwner + 0x20) = (unsigned char)nSlot;
    func_ov002_02052af4(pTask, 0);
}
