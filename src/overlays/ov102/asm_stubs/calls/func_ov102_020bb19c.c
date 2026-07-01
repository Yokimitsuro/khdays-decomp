extern void func_02033d0c(void);

asm int func_ov102_020bb19c(void *arg0, void *arg1)
{
    stmdb   sp!, {r3, lr}
    mov     r3, r1
    ldr     r2, [r0, #8]
    ldr     r1, [r3, #0x138]
    mov     r0, #4
    strb    r0, [r3, #2]
    mov     r0, #0x3000
    str     r0, [r3, #4]
    ldr     r0, [r1]
    mov     r1, #0
    tst     r0, #0x200
    ldrb    r0, [r2, #0x694]
    movne   r1, #1
    mov     r0, r0, lsl #0x1f
    movs    r0, r0, lsr #0x1f
    beq     _done
    add     r2, r3, #0xcc
    mov     r0, #0xd4
    mov     r3, #0
    bl      func_02033d0c
_done:
    mov     r0, #0
    ldmia   sp!, {r3, pc}
}
