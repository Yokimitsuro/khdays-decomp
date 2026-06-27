extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);

asm void *func_0203c6e0(void *list, int key)
{
    stmdb sp!, {r3, r4, r5, lr}
    movs  r4, r1
    mov   r5, r0
    moveq r0, #0
    ldmeqia sp!, {r3, r4, r5, pc}
    bl    func_01fffd70
    cmp   r0, #0
    beq   end
loop:
    ldr   r1, [r0, #0x1c]
    cmp   r1, r4
    ldmeqia sp!, {r3, r4, r5, pc}
    mov   r0, r5
    bl    func_01fffd8c
    cmp   r0, #0
    bne   loop
end:
    mov   r0, #0
    ldmia sp!, {r3, r4, r5, pc}
}
