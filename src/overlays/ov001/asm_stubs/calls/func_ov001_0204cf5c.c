extern void func_ov001_0204ce40();
extern void NNS_FndInitAllocatorForExpHeap();
extern int data_0204c044;
extern int data_0204c048;
extern int data_0204c030;
extern int data_0204c024;
extern int data_0204c034;
extern int data_0204c02c;
extern int data_0204c028;

asm void func_ov001_0204cf5c(void)
{
    stmdb sp!, {r3, lr}
    sub   sp, sp, #8
    add   r0, sp, #4
    add   r1, sp, #0
    bl    func_ov001_0204ce40
    ldr   r1, [sp, #4]
    ldr   r3, =data_0204c044
    ldr   r0, =data_0204c048
    mov   r2, #4
    str   r1, [r3]
    bl    NNS_FndInitAllocatorForExpHeap
    ldr   r1, [sp]
    ldr   r3, =data_0204c030
    ldr   lr, =data_0204c044
    ldr   ip, =data_0204c024
    ldr   r0, =data_0204c034
    mov   r2, #4
    str   lr, [ip]
    str   r1, [r3]
    bl    NNS_FndInitAllocatorForExpHeap
    ldr   r2, =data_0204c030
    ldr   r1, =data_0204c02c
    ldr   r0, =data_0204c028
    str   r2, [r1]
    str   r2, [r0]
    add   sp, sp, #8
    ldmia sp!, {r3, pc}
}
