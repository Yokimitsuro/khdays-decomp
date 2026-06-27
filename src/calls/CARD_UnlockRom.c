extern void OS_UnlockCard_0x0200179c(void *);
extern void CARDi_UnlockResource(void *, int);

asm void CARD_UnlockRom(void *object)
{
    stmdb sp!, {r4, lr}
    mov r4, r0
    bl OS_UnlockCard_0x0200179c
    mov r0, r4
    mov r1, #1
    bl CARDi_UnlockResource
    ldmia sp!, {r4, pc}
}
