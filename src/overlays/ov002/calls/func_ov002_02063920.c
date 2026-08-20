extern int data_ov002_0207f634;

extern void func_ov002_02052af4(int pTask, int nResult);
extern void func_02011988(int nHandle, int *ppInfo);
extern void *NNS_FndAllocFromDefaultExpHeapEx(int nSize, int nAlign);
extern void MIi_CpuCopyFast(const void *pSource, void *pDest, int nSize);
extern void func_ov002_02053d28(int nKind, int nFlags, int pData, int pMeta, int nHandle);

/* Load the palette block for the task's resource: copy 0x40 bytes out of the
 * resource body into a fresh heap block, register it, and finish the task. */
void func_ov002_02063920(int pTask)
{
    int pInfo;
    int pOwner;

    pOwner = *(int *)&data_ov002_0207f634;
    if (pOwner == 0) {
        func_ov002_02052af4(pTask, 1);
        return;
    }

    func_02011988(*(int *)(pTask + 8), &pInfo);

    *(int *)(pOwner + 0x1c) = (int)NNS_FndAllocFromDefaultExpHeapEx(0x40, 4);
    MIi_CpuCopyFast((const void *)(*(int *)(pInfo + 0x14) + 0x1a60),
                    (void *)*(int *)(pOwner + 0x1c), 0x40);

    func_ov002_02053d28(0x16, 0, *(int *)(pInfo + 0x14), *(int *)(pInfo + 0x10),
                        *(int *)(pTask + 8));
    func_ov002_02052af4(pTask, 0);
}
