extern void CARDi_LockResource(void *, int);
extern void OS_UnlockCard(void *);

asm void CARD_LockRom(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    mov r1, #1
    bl CARDi_LockResource
    mov r0, r4
    bl OS_UnlockCard
    ldmia sp!, {r4, pc}
}
