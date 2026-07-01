extern void OS_GetLowEntropyData(void *);
extern int data_0204c174;
extern int data_0204c168;

asm void func_ov001_0204cccc(void)
{
    stmdb sp!, {r4, r5, r6, lr}
    sub   sp, sp, #0x20
    add   r0, sp, #0
    bl    OS_GetLowEntropyData
    ldr   r2, =0x000001ff
    mov   r1, #0
    add   r0, sp, #0
_loop_0204cccc:
    ldr   r3, [r0, r1, lsl #2]
    add   r1, r1, #1
    eor   r6, r6, r3
    eor   ip, r4, r3
    and   r3, r6, r2
    mov   r4, ip, lsl #0x1b
    eor   r5, r5, #0
    mov   r6, r6, lsr #9
    orr   r6, r6, r5, lsl #23
    mov   r3, r3, lsl #0x17
    cmp   r1, #8
    orr   r4, r4, ip, lsr #5
    orr   r5, r3, r5, lsr #9
    orr   r6, r6, #0
    blt   _loop_0204cccc
    ldr   r1, =data_0204c174
    ldr   r0, =0x6c078965
    str   r6, [r1]
    str   r5, [r1, #4]
    str   r0, [r1, #8]
    ldr   r5, =0x5d588b65
    ldr   r3, =0x00269ec3
    str   r5, [r1, #0xc]
    str   r3, [r1, #0x10]
    mov   r2, #0
    ldr   r0, =data_0204c168
    str   r2, [r1, #0x14]
    stmia r0, {r4, r5}
    str   r3, [r0, #8]
    add   sp, sp, #0x20
    ldmia sp!, {r4, r5, r6, pc}
}
