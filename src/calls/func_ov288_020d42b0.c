extern int data_02041dc8;

asm void func_ov288_020d42b0(void *r0)
{
    ldr     ip, [r0, #4]
    ldr     r0, [ip]
    add     r0, r0, #0x100
    ldrsb   r0, [r0, #0xc6]
    cmp     r0, #2
    beq     _020d42b0_skip
    ldr     r0, =data_02041dc8
    add     r3, ip, #0x1c
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
_020d42b0_skip:
    ldr     r1, [ip]
    add     r0, ip, #0x1c
    add     r3, r1, #0xf0
    ldmia   r0, {r0, r1, r2}
    stmia   r3, {r0, r1, r2}
    bx      lr
}
