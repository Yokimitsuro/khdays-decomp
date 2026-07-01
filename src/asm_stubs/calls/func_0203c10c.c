extern void *func_01fffd70(void *list);
extern void *func_01fffd8c(void *list);
extern void  func_0203c86c(void *node, void *arg);

asm void func_0203c10c(void *self, void *arg)
{
    stmdb sp!, {r3, r4, r5, lr}
    mov   r5, r0
    add   r0, r5, #0x88
    mov   r4, r1
    bl    func_01fffd70
    cmp   r0, #0
    ldmeqia sp!, {r3, r4, r5, pc}
loop:
    ldr   r0, [r0]
    mov   r1, r4
    bl    func_0203c86c
    add   r0, r5, #0x88
    bl    func_01fffd8c
    cmp   r0, #0
    bne   loop
    ldmia sp!, {r3, r4, r5, pc}
}
