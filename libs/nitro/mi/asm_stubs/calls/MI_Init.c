extern void MI_SetWramBank(int);
extern void MI_StopDma(int);

asm void MI_Init(void)
{
    stmdb sp!, {r3, lr}
    mov r0, #3
    bl MI_SetWramBank
    mov r0, #0
    bl MI_StopDma
    ldmia sp!, {r3, pc}
}
