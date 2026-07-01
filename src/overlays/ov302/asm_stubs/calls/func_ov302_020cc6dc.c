extern void NNS_FndGetNextListObject(void);

asm void func_ov302_020cc6dc(void)
{
    stmdb   sp!, {r4, lr}
    mov     r4, r0
    add     r0, r4, #0x18
    bl      NNS_FndGetNextListObject
    movs    r1, r0
    beq     _end
_loop:
    ldr     r0, [r1, #0x10]
    cmp     r0, #0
    beq     _end
    add     r0, r4, #0x18
    bl      NNS_FndGetNextListObject
    movs    r1, r0
    bne     _loop
_end:
    mov     r0, r1
    ldmia   sp!, {r4, pc}
}
