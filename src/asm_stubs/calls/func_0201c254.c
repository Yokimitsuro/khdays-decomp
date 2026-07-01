extern unsigned int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(unsigned int);
extern int SND_SetActiveSlotSwap(int);
extern int func_0201b7e0(int);
extern void func_0201b808(int, int);

asm void func_0201c254(int a, int b, int c)
{
    stmdb sp!, {r3, r4, r5, r6, r7, lr}
    movs r4, r1
    mov r7, r0
    mov r6, r2
    ldmeqia sp!, {r3, r4, r5, r6, r7, pc}
    bl OS_DisableInterrupts
    mov r5, r0
    mov r0, r4
    bl SND_SetActiveSlotSwap
    mov r4, r0
    mov r0, r6
    bl func_0201b7e0
    cmp r7, r0
    bne done_clear
    mov r0, r6
    mov r1, #0
    bl func_0201b808
done_clear:
    mov r0, r4
    bl SND_SetActiveSlotSwap
    mov r0, r5
    bl OS_RestoreInterrupts
    ldmia sp!, {r3, r4, r5, r6, r7, pc}
}
