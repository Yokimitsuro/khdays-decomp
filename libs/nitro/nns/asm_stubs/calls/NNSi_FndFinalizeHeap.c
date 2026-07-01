extern void FindListContainHeap(void *);
extern void NNS_FndRemoveListObject(void *, void *);

asm void NNSi_FndFinalizeHeap(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl FindListContainHeap
    mov r1, r4
    bl NNS_FndRemoveListObject
    ldmia sp!, {r4, pc}
}
